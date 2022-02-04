valgrind is an instrumentation framework which does dynamic code analysis. i.e it analysis and reports issues with your code as it is run.
valgrind tool is modular. i.e. you can plugin your own error/code checking tool and use with valgrind. Some of the tools which are available in valgrind are:

1) memcheck: a memory check tool. Identify heap overruns, memory leaks and other types of memory errors

2) Cachegrind: a cache and branch prediction profiler.

3) Callgrind: a call-graph generating cache profiler

4) helgrind: a thread error detector

5) DRD: also a thread error detector

6) Massif: a heap profiler

Valgrind is made up a valgrind core and these tools above. It is designed to be non-intrusive, so you dont need to recompile, relink your program.
You run valgrind like this
prompt$> valgrind [valgrind_options] you_program [your_program_options]

How valgrind works
==================
valgrind executes your code on a synthetic CPU provided by the core. Since your_program is running valgrind, valgrind is the main driver program. it is going to take control of your program. As it sees new code which needs to be executed, this core will handover this code to the selected tool; the tool will instrument it and then hand it back to valgrind core, which will then run the instrumented code.
That is the reason your code runs so much slower in valgrind. 

Also valgrind will instrument all the code, including the glibc library functions and any X11 libraries or 3rd party libraries. If you are not interested in that, you can add them to a suppressions file and valgrind will not instrument it. If you dont know what to add to the suppressions file exactly, you can run valgrind with --gen-suppressions=yes once. It will output a suppression for every reported error, which you can copy into the suppressions file.

The commentary can be output both by the valgrind core and by the tool that you are using. However if there is any profiling output that is usually written to some other output file depending on the tool. So profiling output is not influenced by the -log-* options.


Things to keep in Mind
======================
1) Have you built your code with -g?? You must, so valgrind can report meaningful errors by telling you the filename and line numbers where errors are reported.
2) Stick to using -O0 or -O1. At -O2 and above, the Memcheck tools has a tendency to report errors regarding uninitialized value errors. So to prevent memcheck from reporting any false positives or false negatives, stick to -O0 or -O1 when running memcheck tool.
3) Always enable -Wall. it is a good idea.
4) Use -fno-inline for Debug mode. this will help valgrind produce a cleaner function call-chain. If you cant do this atleast use
   --read-inline-info=yes, so valgrind will read the debug information describing inline information. With this, call chain will be shown properly.
5) Valgrind understand only DWARF 2/3/4 debugging format. It doesnt understand "stabs" format. So use the -gdwarf-2 or -gdwarf-3 or -gdwarf-4 flag.

Valgrind Common Issues
======================


Valgrind Common Flags
=====================
--tool=memcheck --> which tool to use. Default is memcheck.
--gen-suppressions=yes --> out a suppressions string for every reported error. this string can be used to suppress this error.
-v --> get more detailed valgrind commentary.
Example if the same invalid read is occurring repeatedly, the commentary will show only one error followed by the occurrence count.
Also with -v, the valgrind commentary will output each suppression that was used to suppress errors, how many times the error occurred and which suppression file defines it. By default, valgrind defines it a default suppressions file, but you can also define your own.
-vv --> get even more detailed valgrind commentary.
--log-fd=10 --> Output commentary to file descriptor 10. Default is stderr.
--log-filename=filename --> write valgrind commentary to filename.
--log-socket=IP:Port --> to send commentary over a network socket. valgrind even provides a basic valgrind-listener to listen on the other end and dump output to stdout.
--error-limit=no --> dont stop no matter how many errors valgrind reports. generally valgrind will stop after 1000 occurrence of the same error or after 10mio different errors are reported.
--default-suppressions=no --> Don't suppress default suppression defined in $PREFIX/lib/valgrind/default.supp file.
--suppressions=/path/to/file.supp --> can be specified more than one time
--demangle=no --> dont demangle C++ function names in the commentary. Ideally, it should be yes, so the output is clear. But when you want to add a suppression to the suppressions file, at that time, you must give mangled name. So this option can help you get that name exactly to paste in the suppressions file.
--help --> trivial
--quiet --> Run quietly, print only error messages. Also prints Heap Summary and Leak Summary. Useful if you are running regression tests or have some other automated test machinery
-s, --show-error-list=no|yes [default: no]
If this option is enabled, for tools that report errors, valgrind will show the list of detected errors and the list of used suppressions at exit. Enabled by default with -v. --quiet and --show-error-list
--trace-children=<yes|no> [default: no] --> valgrind will trace child process created by exec. Note that valgrind does trace into the child of a fork, as long as it does not call exec. But most child processes exec away, and those wont be traced by default.
--num-callers=<number> [default: 12] --> Specifies the maximum number of entries shown in stack traces that identify program locations.
--keep-debuginfo=<yes|no> [default: no] --> When enabled, keep ("archive") symbols and all other debuginfo for unloaded code. This allows saved stack traces to include file/line info for code that has been dlclose'd (or similar)

--run-libc-freeres=<yes|no> [default: yes] --> This option is only relevant when running Valgrind on Linux.
The GNU C library (libc.so), which is used by all programs, may allocate memory for its own uses. Usually it doesn't bother to free that memory when the program ends—there would be no point, since the Linux kernel reclaims all process resources when a process exits anyway, so it would just slow things down.
The glibc authors realised that this behaviour causes leak checkers, such as Valgrind, to falsely report leaks in glibc, when a leak check is done at exit. In order to avoid this, they provided a routine called __libc_freeres specifically to make glibc release all memory it has allocated. Memcheck therefore tries to run __libc_freeres at exit.
Unfortunately, in some very old versions of glibc, __libc_freeres is sufficiently buggy to cause segmentation faults. This was particularly noticeable on Red Hat 7.1. So this option is provided in order to inhibit the run of __libc_freeres. If your program seems to run fine on Valgrind, but segfaults at exit, you may find that --run-libc-freeres=no fixes that, although at the cost of possibly falsely reporting space leaks in libc.so.
--run-cxx-freeres=<yes|no> [default: yes] --> Ditto like --run-libc-freeres, but for C++
--fair-sched=yes/no/try --> option controls the locking mechanism used to serialise thread execution. should be yes, if platform supports it.

Suppression file format
=======================
{
    name_of_suppression --> any identifying string will do
	
	name_of_tools:supp_kind --> tool name and the suppression name. Example: Memcheck:Cond, MemCheck:Addr4, etc
	
	(Optional extra information for some suppression types, like for Memcheck:Param), example: "write(buf)", "writev(vector[...])"
	
	Remaining lines: This is the calling context for the error -- the chain of function calls that led to it. There can be up to 24 of these lines.
	Locations may be names of either shared objects, functions, or source lines. They begin with obj:, fun:, or src: respectively. Function, object, and file names to match against may use the wildcard characters * and ?.
	Source lines are specified using the form filename[:lineNumber].
}

example:
{
   a-contrived-example
   Memcheck:Leak
   fun:malloc
   ...
   fun:ddd
   ...
   fun:ccc
   ...
   fun:main
}
This suppresses Memcheck memory-leak errors, in the case where the allocation was done by function "main" calling (though any number of intermediaries, including zero) function "ccc", calling onwards function "ddd" and eventually to "malloc".

Thread Support
==============
Threaded programs are fully supported.

The main thing to point out with respect to threaded programs is that your program will use the native threading library, but Valgrind serialises execution so that only one (kernel) thread is running at a time. This approach avoids the horrible implementation problems of implementing a truly multithreaded version of Valgrind, but it does mean that threaded apps never use more than one CPU simultaneously, even if you have a multiprocessor or multicore machine.

Valgrind doesn't schedule the threads itself. It merely ensures that only one thread runs at once, using a simple locking scheme. The actual thread scheduling remains under control of the OS kernel. What this does mean, though, is that your program will see very different scheduling when run on Valgrind than it does when running normally. This is both because Valgrind is serialising the threads, and because the code runs so much slower than normal.

This difference in scheduling may cause your program to behave differently, if you have some kind of concurrency, critical race, locking, or similar, bugs. In that case you might consider using the tools Helgrind and/or DRD to track them down.