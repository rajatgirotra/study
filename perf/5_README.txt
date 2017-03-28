"perf report"
This command reads perf.data and brings up an ncurses interface. By default you see the following columns

1) The percentage of all the samples collected in the function specified in column 5.
2) If samples are collected on a per thread or per process, this is the process name. If samples are collected on a per cpu mode, this is the
   name of whatever process was running on the cpu at that time
3) The name of the ELF library where the function is defined.
4) The priviledge level of the cpu at the time the sample was taken
    . (dot) means user space
    k means kernel
    g means guest kernel level
    u means guest os user space
    etc etc
5) and finally the function name.

There are many options for "perf report". See help

--sort=dso (to sort on column 3)

When samples come from kernel space the ELF image name in column 3 is always (kernel.kallsyms)
Sometimes function name (column 5) shows a hexadecimal address. This is when the ELF image does not have a symbol table (because it is stripped)

Tip
===

Let say you are sampling over all cpus (using -a option with perf record). You can then quickly view if all CPU's look balanced
by looking at percentage in column 1 and sorting with --sort=cpu

"perf report --sort=cpu"

Also write some sample c++ code and try to generate perf.data and try to analyse with perf report.

You can also specify options to record the call graph (ie stack backtrace) and list the times spent in each function


"perf annotate" is used to go down more deeply into the instruction level (assembly level) execution
perf can also show you the c++ code corresponding to the assembly if you compile with --ggdb

Also for kernel code annotation, you need to make sure that kernel is compiled with debug symbols,
and pass the path of the UNCOMPRESSED kernel using the -k option

perf annotate -k /tmp/vmlinux -d symbol
