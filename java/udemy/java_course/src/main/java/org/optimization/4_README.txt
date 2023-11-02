Profilers
=========
Profiling tools are the most important tools for finding out bottlenecks in your code. There are many different profiling tools available. Each tool
will have its own UI and its own way of reporting and pinpointing issues.

Many profiling tools are written in Java itself, and they attach to the main application you are profiling using a socket or the native Java interface called
JVMTI (JVM Tool Interface). Because these profiling apps can receive volume of profiling data over the attached socket or interface, these profiling apps
should themselves also be optimized to handle large profiling data. You can consider running the profiler with concurrent GC algorithm as well, otherwise
an ill-timed full GC pause in profiling can cause the buffers in the profiling tool to overflow.

 here are two main types of profiling:

Sampling profilers
------------------
Sampling profilers have a timer thread which goes off at regular intervals. At each interval, the profiler will wake up and trace all the threads in your application,
and determine which thread each thread is running. That method is then charged with having been executed since the timer previously fired.

Sampling profilers are subject to all sorts of sampling errors. Let's say two methods methodA and methodB are executing and methodA is executing longer than methodB.
However, each time profiler thread executes, it finds methodB executing. That's why it is recommended to run the profiler longer and also reduce the time
interval between samples.
However running the profiler longer is also not very good, as profiling is intrusive and it can affect the overall performance numbers of your application.
So it is advised to strike a balance here.

The other issue with some of the old Java based profilers is that they used the Java common interface for profilers. that interface only allows the profiler thread
to take a stack trace of a thread when the thread has reached a safe point. i.e. the thread is blocked on a lock or monitor or I/O, or thread is blocked or
executing some JNI code. This can have a profound impact on measurement, and the sampling becomes even less reliable.

Java 8 introduced another way for profilers to get stack traces which does not require safe point bias. This is done using the AsyncGetCallTrace interface.
That's why profilers which use this interface are called async profilers.

Instrument Profilers
---------------------
Instrument profilers are much more intrusive than sampling profilers, so you should use them with caution. These profilers work by altering the bytecode of your application
class files as they are loaded (like adding code to count method invocations etc). Since they can have a performance impact on your application, only use them as for second level
analysis. So you could stick to sampling profilers first, and only add those sections (packages, class files) of your code under instrument profilers where you know is the real
bottlenecks in your code. That limits their impact on the application’s performance. Normally instrument profilers will filter out private methods and only show public interfaces
in the instrumented results.

Blocked Threads
---------------
Some profilers might even filter out thread which are blocked (may be on a lock/monitor, or network I/O, or a wait() call etc). Most of the time this is OK. But sometimes
you should check your code and ascertain that the blocked threads are OK and expected.

Native Profilers
-----------------
Some profilers can also profile native (C/C++) code which is very helpful. If a native profiler shows that time in GC dominates the CPU usage, tuning the collector is the right thing to do.
If it shows significant time in the compilation threads, however, that is usually not affecting the application’s performance.