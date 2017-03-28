perf is a linux profiling tool; also called linux perf_events (LPE) or performance counters for linux (PCL)
Perf is based on the perf_events interface exported by recent versions of the Linux kernel

Get it here:
sudo apt-get install linux-tools-common OR sometimes
sudo apt-get install linux-tools-3.13.0-63-generic

It is used for instrumenting CPU performance counters. Each CPU has performance counter registers (hardware registers) which count information like:

1) number of instructions executed
2) number of cache misses
3) number of branches mispredicted etc..
These are a general or specific registers for couting event count. Based on architecture, there count is fixed. The general registers can count any event, and the specific registers can only count a certain type of event.
If you specify more number of events in the perf command, than there are registers available for counting, perf will do multiplexing at some frequency F (normally whatever SZ is set to, 100 or 1000) and then report a final count by scaling it up. Eg: if an program ran for 15 minutes, and the event counter only counted till 300 in 5 minutes, final count will be:
300 * 15/5 = 300 * 3 = 900 (simple).
So when running perf, try to find the number of counter registers available for your architecture and try to avoid scaling. Note that multiplexing only applies to PMU events.

You can say that perf is an event counter. All the above 3 and many other types of events are there in linux. perf_events module just maintains a count; and exposes it via
the perf tool.

These actually form the basis for profiling applications to trace dynamic control flow and identify hotspots in code.
Obviously for application profiling you are more interested in higher level detail like time taken to execute the function, number of times a function gets called., memory used etc. Perf provides a rich set of
generalized abstractions over hardware specific capabilities (so it abstracts away CPU hardware differences between different systems and presents a simple command line interface for perforamce measurements).

Also you can add tracepoints in your application code. These are locations in your code where you do important things like:
1) Making a system call.
2) Or you do a file system operation
3) Socket reading/writing etc.
When not in use, these tracepoints have negligible overhead. But you can enable them using perf command to collect important information like timestamps and stack traces.
Also perf provides a way to dynamically create tracepoints using kprobes (for kernel profiling) or uprobes (for user application profiling) frameworks.

The perf command interface is like git where you have specific commands to do specific tasks.

1) perf stats : will return event counts
2) perf record : will record events for later reporting
3) perf report : break down events by function, process etc.
4) perf annotate : read perf.data file (produced by perd record) and display annotated code
5) perf top : see live event count
6) perf bench : run different kernel microbenchmarks.

and many more commands we'll learn along the way

perf help <commandName> for more help on any specifc command OR
perd <commandName> -h (for a list of options for that command)
