JIT (Just in Time Compiler)
===========================
You already know that C++ is compiled language and that languages like PHP/Python are interpreted. So we can copy the python source
code on any host which has the python interpreter. The python interpreter will line by line translate the source code into binary and
run it on that host.

Java takes a mix of both approaches.
1) First the javac compiler will translate all source code into intermediate bytecode. This bytecode is platform-agnostic so the java class files
can be copied to any host.
2) the java program will then only the fly translate this bytecode into machine code i.e. binary code which can be executed on the target host.

However, in a large application, there will always be one or more sections of code which are executed more often than other parts of the code.
These sections of the code are actually called HotSpots i.e. they are the critical sections of the code which determine the overall performance of the code
base.

So JVM can decide to compile these HotSpot sections of code and cache it internally. So that multiple executions of the same section need not require re-translating
from bytecode to machine code un-necessarily. The CPU time spent on compilation and caching definitely outweighs the cost of multiple translation cycles.

But how and when does this compilation happen?

1) When a java program starts, it doesn't start compiling every piece of code immediately. That's because
   a) It doesn't have enough information on the HotSpots in the code. What if JVM compiles a section of code which is only run/interpreted once.
   b) the second reason is optimization. The more a section of code is executed, the more information Java has about that section of code. Like the call stack information
      when the method is called, the method parameters with which a method is called. the exceptions that can be thrown etc. All this information allows JVM to produce highly
      optimized compiled code.

One of the most important optimizations a compiler can make involves when to use values from main memory and when to store values in CPU registers.
Register usage is a general optimization of the compiler, and typically the JIT will aggressively use registers.

-XX:+TieredCompilation
======================
Very old Java versions shipped with two separate compilers. These were called client compiler (called C1 compiler) and server compiler (called C2 compiler) and users had to choose
between one of them using either -client or -server flag. What was the difference between C1 and C2 compilers?
C1 compiler compiled early. So code got faster soon. But the compiled code lacked optimizations which the C1 compiler could not apply as it did not have enough information on the HotSpot sections
of the code. C2 compiler waited some time to understand better the HotSpot sections and later on compiled the code applying a lot of optimizations. So initially code was slower,
but later on it got much faster compared to C2 compiler.

Nowadays, both -client and -server flags are deprecated. java binaries ship with both compilers and by default -XX:+TieredCompilation flag is on which means both C1 and C2 compilers
will work together to make code faster.

The only reason you may be inclined to turn off TieredCompilation is when running in a memory-constrained environment for example: in a docker container with resource constraints.
Or you may be running dozens of JVMs on your large machine. In those cases, you may want to reduce the memory footprint of your application. and how is memory saved? Actually, only
the C2 compiler will compile code and C1 compiler is disabled. Since the C1 compiler compiles early, it compiles far more classes than C2 compiler, so you need a bigger Code Cache.
with C1 compiler disabled, you won't need as big a code cache.

If we disable TieredCompilation and have a sufficiently longer warm-up period, we still might be able to get the same performance, as all the HotSpots will get compiled eventually.
The only thing is that our application will be slower initially. However, there still might be some methods that are compiled by C1 compiler and may not be compiled by C2 compiler,
due to which TieredCompilation might still be a better choice.

Please note that the C2 compiler in Oracle JDK is called the standard compiler, and it is written in C++.

-XX:InitialCodeCacheSize & -XX:ReservedCodeCacheSize
====================================================
As JVM compiles code, it stores the set of assembly language instructions generated in the code cache. The cache has a limited capacity. and when it is reached, JVM stops compiling
code any further. This means a lot of HotSpot sections of the code can run very slowly as it will be interpreted only.
java throws out warning when compilation stops:
"Java HotSpot(TM) 64-Bit Server VM warning: CodeCache is full.
Compiler has been disabled.
Java HotSpot(TM) 64-Bit Server VM warning: Try increasing the
code cache size using -XX:ReservedCodeCacheSize=
"
To get around the problem, just increase the size of the reserved code cache size. You can always find out the default on your system using "jinfo".
"jinfo -flag InitialCodeCacheSize <processID>"
"jinfo -flag ReservedCodeCacheSize <processID>"

Normally if you run out of CodeCache memory, just double it.

If you want to Reserve a very high cache size so that jvm never stops compiling, you must ensure you have such large virtual memory available to your process.
By default, Initial is 2496KB and Reserved is 240MB.

The size of the code cache (and the JDK 11 segments) can be monitored in real time by using jconsole and selecting the Memory Pool Code Cache chart on the Memory panel.

Reserved Vs Allocated Memory
============================
It is important to understand the distinction between how the JVM reserves memory and how it allocates memory. This difference applies to the code
cache, the Java heap, and various other native memory structures of the JVM.

-XX:+PrintCompilation
======================
There are multiple threads in JVM which can compile code. Whenever a thread compiles a loop or a method, and the -XX:+PrintCompilation flag is on, JVM will spit out a line something like this:
"timestamp compilation_id attributes (tiered_level) method_name size deopt"
timestamp -> timestamp after the compilation is completed. starting from 0 where 0 is the JVM start time. value is in milliseconds. Divide by 1000 to get the value in seconds.
compilation_id -> an internal task id. normally monotonically increasing.
attributes -> This is a 5 character string which gives more information on what was compiled and how. These characters are:
   % -> the compilation is OSR (On Stack Replacement).
   s -> the method was synchronized
   ! -> the method has an exception handler
   b -> the code was compiled in blocking mode rather than continuing interpreting and using compiled code on the next iteration (if available). -XX:+BackgroundCompilation is used to control it.
   n -> JVM generated compiled code to facilitate the call into a native method.
tiered_level --> Level of the C1 or C2 compiler which compiled the code. If Tiered Compilation is off, it will be blank. valid values are 0, 1, 2, 3, 4
method_name --> Trivial: ClassName::method
size --> size in bytes of the Bytecode that has been compiled
deopt --> meaning, some sort of de-optimization has taken place. We will come to de-optimization later.

Use can use jstat also to print some limited information about methods that are compiled.
jstat -compiler <processID> 1000 -> means every 1000ms or 1 sec, show the number of methods compiled by JVM. Also show how many failures occurred.

If sometimes JVM compilation thread fails, you get an output.
"timestamp compile_id COMPILE SKIPPED: reason"
This is mostly when Code Cache is filled or Concurrent classloading happened (i.e. the class was being modified as it was compiled). In all failure cases,
the compilation should be reattempted by the JVM.

Tiered Levels
=============
There are 5 levels at which code can be compiled even though we have only C1 and C2 (i.e. 2) compilers. There are 3 levels for C1 compiler
0 -> Interpreted code
1 -> Simple C1 compiled code
2 -> Limited C1 compiled code
3 -> Full C1 compiled code
4 -> C2 compiled code
All methods start at level 0, of course, but that doesn't appear in the log. the most frequent path is leve 0 --> level 3 --> level 4.
If a method runs often enough, it will get compiled at higher level 4, and the level 3 code will be made not entrant. Sometimes when C2 compiler queue is full,
methods will be pulled out of level 4 and compiled at level 2. Later on, it will get compiled at level 3 and level 4.

When the code is de-optimized, it goes to level 0.

De-optimization
===============
De-optimization means the compiled code has to be undone. This is done in two cases.
 1) When compiled code is made not re-entrant.
 2) When compiled code is made a zombie.
We will understand the specifics later, but usually de-optimization is the process by which the JVM replaces previously compiled code. This usually happens in the
context of C2 code replacing C1 code, but it can happen because of changes in the execution profile of an application.

Compilation Threshold
=====================
CompilationThreshold flag is -XX:CompileThreshold=N
Basically in the JVM, there are two counters that decide some section of code must be compiled. One counter is the number of times a method is called and the other is the
number of times a loop is executed. By setting CompileThreshold, you alter this counter threshold value. Note that this setting has no effect if TiredCompilation flag is ON.
The default value of this flag is 10000, but some JVM lower it to 8000 so that code can get compiled quickly and become faster quickly.
Normally these days all JVM have TieredCompilation flag ON, so you don't need to touch this flag.

Also, if your application is running long enough, won't all the code get compiled eventually? No it doesn't work like that. These counters also get reduced by JVM over time.
So the value of these counters only give you the recent Hotness of method or a loop.

Instead, you can modify -XX:Tier3InvocationThreshold=N (default 200) to get C1 to compile a method more quickly,
and -XX:Tier4InvocationThreshold=N (default 5000) to get C2 to compile a method more quickly to get slight improvements in speed.

Compiler Threads
================
JVM can have multiple threads to compile code (methods and loops). The number of threads depend on the number of cores on the target OS. There is a table we can lookup
to see how many threads JVM will use. Also, when JVM decides to compile a method or loop, it actually queues the request for compilation. And JVM has separate queues for
both C1 and C2 compilers. By default, JVM will allocate one third of the threads to C1 queue and the rest to C2 queue. Also, requests are queued based on priority i.e. the number of times a method or loop is executed, because HotSpots in code should be compiled first
naturally to get the speedup.

-XX:CICompilerCount=N is used to specify the total threads JVM should use. By default, same policy will apply. 1/3rd to C1 compilation and 2/3rd to C2 compilation.
if TieredCompilation is disabled, JVM will only start the C2 compiler threads according to its table. No C1 compiler threads will be started.

When might you consider adjusting this value? Because the default value is based on the number of CPUs, this is one case where running with an older
version of JDK 8 inside a Docker container can cause the automatic tuning to go awry. In such a circumstance, you will need to manually set this flag to the
desired value.

Also, almost always -XX:+BackgroundCompilation should be set to true, so compilation can continue on background threads instead of blocking the application code, doing compilation
and then continuing the application by using the compiled code.

Inlining
========
It is such an important performance flag. Disabling inlining using -XX:-Inline can lead to 50% performance loss. By default, it is always enabled.
The basic decision about whether to inline a method depends on two things
1) how hot it is: i.e. how frequently is it called.
2) and its size.
If a method is eligible for inlining because it is called frequently, it will be inlined only if its bytecode size is less than 325 bytes (or whatever is
specified as the -XX:MaxFreqInlineSize=N flag).

Otherwise, it is eligible for inlining only if it is smaller than 35 bytes (or whatever is specified as the -XX:MaxInlineSize=N flag).

Escape Analysis
===============
the C2 compiler can perform some aggressive code optimizations if the -XX:+DoEscapeAnalysis is set to true (by default it is true only).
No need to touch this flag

CPU Specific code
=================
Of course the JVM need to compile code for the target instruction set. But the target instruction set might have newer and better instruction available which may or may
not be supported by the version of Java you are running. Generally we don't need to worry too much about this. But if you are curious to know which AVX instruction set your java
application is using, or you want to explicitly ask your java application to use a particular instruction set, use the -XX:UseAVX=N flag.
0: Use no AVX instructions.
1: Use Intel AVX level 1 instructions (for Sandy Bridge and later processors).
2: Use Intel AVX level 2 instructions (for Haswell and later processors).
3: Use Intel AVX-512 instructions

Javac Compiler
==============
Has no bearing on performance as it only produces bytecode. However, JDK 11 introduces a new way of doing string concatenation that can be faster than previous versions,
but it requires that code be recompiled in order to take advantage of it. That is the exception to the rule here.

GraalVM
=======
GraalVM is a universal virtual machine. This means it can interpret not only Java bytecode, but other interpreted languages like PHP, Python, R etc. GraalVM has two kinds
of releases. One is community edition release, and the other is the enterprise release. The good thing about GraalVM is that:
1) it can run as a regular JVM, but with a new C2 compiler which is written in Java, not in C++ (Oracle JDK standard compiler is written in C++). We call it the GraalVM JIT.
2) it allows you to compile all the code upfront and produce fully native binaries, so you don't need a JVM at run time. (We will not discuss this for now, maybe some time later)

This GraalVM JIT is also available in traditional JVM (OracleJDK/OpenJDK), but you need to enable it using the following flags
a) -XX:UnlockExperimentalVMOptions
b) -XX:EnableJVMCI
c) -XX:UseJVMCICompiler

We can always the performance of running
1) Oracle/OpenJDK with Standard Compiler
2) Oracle/OpenJDK with GraalVM JIT
3) GraalVM with GraalVM JIT

Ahead of time (AOT) compilation
-------------------------------
GraalVM allows AOT compilation -> AOT allows you to compile part or all of your code in advance before running it. This compiled code becomes a shared library (C++ shared library)
which JVM uses when starting your java application. To create a shared library you need to use the tool "jaotc" of the GraalVM. This compilation is done using the C1 compiler of GraalVM.
So your code should initially run at least as well as the C1 compiled code without having to wait for that code to be compiled.
Example of running jaotc:

jaotc --compile-commands=/tmp/methods.txt \
      --output JavaBaseFilteredMethods.so \
      --compile-for-tiered \
      --module java.base

compile-commands -> a file which contains commands specifying which methods to be compiled.
output -> name of the shared library
compile-for-tiered -> compile code such that it is still eligible for C2 compilation inside the JVM
module -> either a java module or set of classes or packages which should be compiled.

To generate the compile-command file, you can run:
java -XX:+UnlockDiagnosticVMOptions -XX:+LogTouchedMethods -XX:+PrintTouchedMethodsAtExit <other arguments>

Finally, your application can load the shared library using:
java -XX:AOTLibrary=/path/to/JavaBaseFilteredMethods.so <other args>

Then you can use the -XX:+PrintAOT flag to produce output whenever a precompiled method is used by the JVM.