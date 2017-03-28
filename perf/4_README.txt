perf record

The perf record command is used to record sampled perf events to a binary file perf.data which can
be later analysed using "perf report" or "perf annotate".

Perf record sampling happens on the basis of event count and not on the basis of timer ticks.
This means you can specify the event on which you want to sample. And the number of occurrences of that event.
The moment the event counter goes past what is given, perf will sample and write a sampling record to perf.data

Basically there are two ways you can specify this sampling frequency.
1) As you just read above, just tell which event you want to sample on and on how many occurences
2) A target number of samples/sec. In this case, the linux kernel will dynamically try to establish the number of occurrences
   of the event which result in the specified sampling rate. This is also the default.

Example of the two cases are

perf record -e instructions:u -F 250 sleep 4  --> ie sample based on the number of instructions executed in user space and at a sampling rate of 250 samples
perf record -e instructions:u -C 2000 sleep 4  --> ie sample based on the number of instructions executed in user space and when that count reaches 2000 

By default "perf record" works in thread mode. You can use similar switches as in "perf stat" to sample on a per cpu mode (-a) or a subset of CPU's (-C 0,2-3)

"perf record -callgraph command" will enable call graph ie backtrace and stackframe tracing

Side note
=========
The perf record command tells you how many samples it has written to perf.data file. This is a wrong indication; so just ignore this.
Use the following command to see how many samples are actuall writtem

"perf report -D -i perf.data | grep RECORD_SAMPLE  | wc -l"



