There are many kinds of events that can occur, majorly

Software events : Ie events generated purely by the kernel, such as context switches, minor faults
Hardware events : Like number of cycles executed, L1 cache misses etc.
tracepoint events: implemented by the kernel ftrace infrastructure.
PMU - Each processor has a PMU (performance management unit) which provides a list of events. These are CPU specific and documented by the CPU vendor
cache events : like TLB specific events.

A lot of these events may also be duplicated.

To obtain a list of supported events:
do 

1) perf list [hw|sw|cache|pmu|tracepoint|event_glob]
These give you the event names to view their counts in most of the other commands using the "-e" options
Also do "perf help list" to see more information


2) Simple way of profiling:
Use "perf stat -e <eventName> -B -a <command>
By default, perf stat will run the command and dump stats on stdout. You can use -e option to dump any specific option you are interested in.
-B means print numbers using thousands separator in the local locale.
-a means aggregate counts from all cpu-s together. To negate this use -A (meaning no-aggregation across CPU's)

"perf stat -B -e cycles:u,instructions dd if=/dev/zero of=/dev/null count=1000000"
Here in cycles:u, u is a modifier (or filter) to print events only at user space level. For kernel use cycles:k
Many other modifiers are available.

Sometimes for PMU events, the CPU vendor can list the raw address of the register to monitor. To read the Performace counter for a specific CPU
use
perf stat -e r1a8 -a sleep 1
Please see the Intel pdf in this folder which has raw address to count many different types of Hardware PMU events.

perf stat -B -r 5 sleep 2
Runs "sleep 2" five times over and gives you the average time over all the runs.
