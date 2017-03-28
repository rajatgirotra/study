Perf can count events on a per-thread, per process or per-cpu basis.

Per-thread - Perf will count events only for that thread. When the thread migrates to a different CPU, perf will migrate the the saved counters onto the new one.

Per-process - Extension of per-thread really. events are counted on a per-process basis. All counts and samples are aggregated at the process level. By default, perf supports automatic inheritance. This means that if your process does a fork() or creates new threads (pthread_create()), all the counts and samples for these processes and threads will be aggregated.

Per-cpu - all threads running on the designated processors are monitored. Use the -C option to specify the list of cpus across which events are counted.

Important Stuff
===============
perf stat -B -ecycles:u,instructions:u -a dd if=/dev/zero of=/dev/null count=2000000
Will count events on all the cpu's. So this command doesn't just count the events for the "dd" program. But counts across all cpu's. Specifying -a means aggregate total across
all cpus.

perf stat -B -ecycles:u,instructions:u -A dd if=/dev/zero of=/dev/null count=2000000
The only change is from "-a" to "-A" (ie no-aggregation). This will report the counters individually for each CPU' and will not aggregate in the output

perf stat -B -ecycles:u,instructions:u -a -C 0-2 dd if=/dev/zero of=/dev/null count=2000000
Same as first one, but only count across cpu's 0, 1 and 2.

perf stat -B -ecycles:u,instructions:u -A -C 0-1 dd if=/dev/zero of=/dev/null count=2000000
Same as second one but dont aggregate counts. Show CPU0 and CPU1 counts separately

SO REALLY NONE OF THE CALLS ABOVE ACTUALLY MEASURES THE COST OF THE DD COMMAND.

So by now, you have seen the following options with perf stat

-B - Display numbers using 1000's separator
-a - Aggregate counts
-A - Dont aggregate counts
-C - Specify a cpu list to use for performance counting
-e - Specify one or more event names for perf to count
-p : see below 
-t : see below
-x<delimiter> : To print output with the specified delimiter. To be read by scripts

Attaching to a process: You can attach to a process or thread and gather stats for that process or thread.
To attach to a process use -p option.
To attach to a thread use -t option.

when attaching to a process or thread, perf will continue to collect stats until it is killed. Alternately, you can give it a command
like "sleep 2" and it will only monitor for the duration of the command. Example

perf stat -B -p pid -e cycles,instructions sleep 2
perf stat -B -t thread_id -e cycles,instructions sleep 2

perf stat has an option -x to display output in a format that can be parsed by script.
