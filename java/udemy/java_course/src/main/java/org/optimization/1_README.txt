What is JVM
============
Java virtual Machine. There are many implementations of the JVM, both as open source and as enterprise.
It has:
GC (Garbage Collector) -> Handles memory allocation and destruction
JIT (Just in Time Compiler) --> will optimize your code and convert to machine code.
Has a security mechanism so that no malicious code from outside can creep into the JVM.

Examples of JVM are:
1) HotSpot is the open source JVM implementation from OpenJDK.
2) Azul Platform Prime – a fully compliant, high-performance JVM based on OpenJDK that uses Azul Systems's C4 garbage collector
and Falcon JIT compiler.
3) Eclipse OpenJ9 – open-source from IBM J9
etc.

JVM is just the runtime in the JDK. JDK contains many tools which are used for studying and optimization a JVM. So it is
important we deploy JDK to production so that we can use these tools for studying JVM behavior and statistics.

which JDK should we use
1) for Java 8, at-least version 222 and higher. Why?
JDK8u222 contains many of the important performance enhancements and features we will discuss below.
2) for JDK 11, at-least version 5 and higher.

All JVM implementations will have one or more garbage collectors, but the flags to tune each vendor’s GC implementation are product-specific.
Here we discuss only flags for Hotspot JVM.

JVM tuning flags -> Are of two types.
Boolean flags -> used to turn on or off certain features. -XX:+FlagName to switch ON, -XX:-FlagName to switch off.
Flags with Parameters -->  -XX:FlagName=FlagValue

When JVM is run, it can figure out default values for a lot of flags on its own. It is based on the target architecture of which
JVM is running + the flags passed to JVM. The process of automatically tuning flags based on the environment is called ergonomics.
Later you will see how we can print all the flag of JVM to console. and JVM will show if these values are figured out ergonomically or not.

Hardware Platforms
==================
Multicore systems
-----------------
From a performance perspective, the important thing about a machine is its number of cores. Let’s take a basic four-core machine:
 each core can (for the most part) process independently of the others, so a machine with four cores can achieve four times
the throughput of a machine with a single core. (This depends on other factors about the software, of course.)

In most cases, each core will contain two hardware or hyper-threads. These threads are not independent of each other: the core can run only one of them at a time. Often,
the thread will stall: it will, for example, need to load a value from main memory, and that process can take a few cycles. In a core with a single thread, the thread stalls at
that point, and those CPU cycles are wasted. In a core with two threads, the core can switch and execute instructions from the other thread.

So our four-core machine with hyper-threading enabled appears as if it can execute instructions from eight threads at once (even though, technically, it can execute only
four instructions per CPU cycle). To the operating system—and hence to Java and other applications—the machine appears to have eight CPUs. But all of those CPUs
are not equal from a performance perspective. If we run one CPU-bound task, it will use one core; a second CPU-bound task will use a second core; and so on up to four:
we can run four independent CPU-bound tasks and get our fourfold increase in throughput.

If we add a fifth task, it will be able to run only when one of the other tasks stalls, which on average turns out to happen between 20% to 40% of the time. Each additional
task faces the same challenge. So adding a fifth task adds only about 30% more performance; in the end, the eight CPUs will give us about five to six times the performance
of a single core (without hyper-threading).

Garbage collection is very much a CPUbound task, so later we will see how hyper-threading affects the parallelization of
garbage collection algorithms.

Containerized systems
---------------------
Two containers here are important. First is the virtual machine, which sets up a completely
isolated copy of the operating system on a subset of the hardware on which
the virtual machine is running. From Java’s perspective (and the perspective of other applications), this virtual
machine is indistinguishable from a regular machine. So for tuning and performance purposes, you need only consider it in the
same way.

The second container of note is the Docker container. A Java process running inside a docker container doesn't necessarily know it is in such a container
 (though it could figure it out by inspection), and the docker container itself is also a process (potentially
with resource constraints) running on the OS.

By default, a Docker container is free to use all the machine’s resources: it can use all the available CPUs and all the available memory on the machine.
But frequently we want to deploy multiple Docker containers on a machine and restrict the resources of each container. In effect, given our four-core machine with 16 GB of memory,
we might want to run two Docker containers, each with access to only two cores and 8 GB of memory. Configuring Docker to do that is simple enough, but complications can arise at the
Java level. Numerous Java resources are configured automatically (or ergonomically) based on the size of the machine running the JVM.
 1) This includes the default heap size and
 2) the number of threads used by the garbage collector
 3) and some thread pool settings
If you are running a recent version of Java 8 (update version 192 or later) or Java 11, the JVM handles this as you would hope: if you limit the docker container to use
only two cores, the values set ergonomically based on the CPU count of the machine will be based on the limit of the Docker container.
Similarly, heap and other settings that by default are based on the amount of memory on a machine are based on any memory limit given to the Docker container.

So earlier versions of JVM would run suboptimally using docker. it will start too many threads and will set up too large a heap. Having too many threads will lead to some
 performance degradation, but the real issue here is the memory: the maximum size of the heap will potentially be larger than the memory assigned to the Docker container.
  When the heap grows to that size, the Docker container (and hence the JVM) will be killed.

Docker containers provide one additional challenge to Java: Java comes with a rich set of tools for diagnosing performance issues. These are often not available in a Docker
  container. We’ll look at those issues later.

Write better code
------------------
JVM can be optimized only to a certain level. The other equally important factor is people writing performant code. Always write good algorithms.
Also, as far as possible, try to achieve more by writing less code. Why?? small well-written programs will run faster than a large well-written program.
This is generally true for all computer programs, and it applies specifically to Java programs. The more code that has to be compiled,
the longer it will take until that code runs quickly. The more objects that have to be allocated and discarded, the more work the garbage collector has to do. The more
objects that are allocated and retained, the longer a GC cycle will take. The more classes that have to be loaded from disk into the JVM, the longer it will take for a
program to start. The more code that is executed, the less likely that it will fit in the hardware caches on the machine. And the more code that has to be executed, the
longer that execution will take.

Example:
Poor code:
"log.log(Level.FINE, "I am here, and the value of X is " + calcX() + " and Y is " + calcY());"

better code:
if (log.isLoggable(Level.FINE)) {
log.log(Level.FINE, "I am here, and the value of X is {} and Y is {}", new Object[]{calcX(), calcY()});
}

This avoids the string concatenation altogether (the message format isn’t necessarily more efficient, but it is cleaner), and there are no method calls or allocation of the
object array unless logging has been enabled.

Benchmarking Code In Java
=========================
Microbenchmark
--------------
Microbenchmark involves testing the performance of a certain smaller unit of code to decide which of the many alternatives perform better. However, certain features of Java
like Just In time compilation and GC may make it difficult to write microbenchmark correctly. Why?
1) Normally, the Java code is interpreted the first few times it is executed, and it gets faster the longer it is executed. For this reason, all benchmarks
   SHOULD TYPICALLY INCLUDE A WARM-UP PERIOD during which the JVM is allowed to compile the code into its optimal state. That optimal state can include a lot of optimizations.
   For microbenchmarks, a warm-up period is required; otherwise, the microbenchmark is measuring the performance of compilation rather than the code it is attempting to measure.
   Example:
   public void doTest() {
      double l;
      // Warmup JVM
      for (int i = 0; i < nWarmups; i++) {
         l = fibImpl1(50);
      }
      // Actual benchmark
      long then = System.currentTimeMillis();
      for (int i = 0; i < nLoops; i++) {
         l = fibImpl1(50);
      }
      long now = System.currentTimeMillis();
      System.out.println("Elapsed time: " + (now - then));
   }
 Since the value of l is not read anywhere, the compiler is free to skip its calculation altogether. So you might get 0 as the result. In practice, changing the definition
 of l from a local variable to an instance variable (declared with the volatile keyword) will allow the performance of the method to be measured.

 Even after this, the code may exhibit different performance in a server environment compared to what you see in microbenchmark environment. Why? because the JVM uses
 profile feedback of code to decide the best optimizations to employ when compiling a method. JVM takes into effect things like
 1) Which methods are frequently called
 2) the stack depth when a method is called
 3) the actual type of the arguments when a method is called and so on - so it is dependent on the environment in which the code actually runs.

 Also, GC may behave different in microbenchmark environment compared vs actual server environment. Consider two alternate implementations
 1) First one runs fairly quickly but produces many short-lived objects.
 2) Second one is slightly slower but produces few short-lived objects.
 First implementation might be better in microbenchmark, because all-though many GC cycles will trigger, they will be quick and discard all short-lived objects in Young generation.
 However, in server environment, since many threads are running, the young generation may get filled up very fast and many objects may be promoted to the old generation required
 full GC cycle to execute.

 Microbenchmark is still very popular and OpenJDK has a core framework to develop microbenchmarks: the Java Microbenchmark Harness (jmh).
