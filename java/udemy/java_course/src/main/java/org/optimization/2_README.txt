Tools available
===============

Tools at OS Level
=================
At OS level, we must at-least capture the usage of CPU, memory and disk as our application is running. These captured results can be later plotted using any graph and charting tool.
If network is also involved, we must capture network stats also. The most important commands available on Unix like systems are:

vmstat -> for CPU stats
iostat -> for disk stats
prstat -> for memory stats
nicstat -> for network stats

The goal in performance is to drive CPU usage as high as possible for as short a time as possible. That may sound a little counterintuitive but let's understand that.
The first thing to keep in mind is that the CPU usage number is an average over an interval—5 seconds, 30 seconds, perhaps even as little as 1 second. Say that the
average CPU usage of a program is 50% for the 10 minutes it takes to execute. This means that the CPU is idle for half the time; if we can restructure the program to not
have idle patches (nor other bottlenecks), we can double the performance and run in 5 minutes (with the CPU 100% busy). If then we improve the algorithm used by the program
and double performance again, the CPU will still be at 100% during the 2.5 minutes it takes the program to complete. The CPU usage number is an indication of how effectively
the program is using the CPU, and so the higher the number, the better.
So as you see above, you need to drive CPU usage as high as possible for as short a time as possible.

Tools at JDK level
==================
JDK provides many tools. Example:

jcmd -> Print basic information of a Java process like class usage, thread usage and JVM information.
jconsole -> Graphical tool to view JVM activities and GC activities.
jmap -> Provides heap dumps and other information about JVM memory usage. Can be used for postprocessing.
jinfo -> Provides information on System properties of the JVM. Can be used to also dynamically set some properties on the JVM.
jstack -> Dump the stack of a Java process.
jstat -> Provides information on class loading and GC activities.
jvisualvm -> Another gui tool to monitor JVM

all the command line tools should be installed inside the docker container itself as part of JDK. graphical tools like jconsole requires system resources, so running it on the
production host may interfere with your main application performance. So always run jconsole locally, and attach it to a remote JVM using SSL.

These tools fit into these broad areas:
• Basic VM information
• Thread information
• Class information
• Live GC analysis
• Heap dump postprocessing
• Profiling a JVM
