Java Garbage Collection
=======================
You already know Java doesn't require the user to manage object lifetimes. It is handled internally by the JVM's Garbage Collector framework.
Users carefully need to tune and understand GC because it can have a profound impact on your application's performance. Since you need to
understand the GC internals and concepts, some people argue it would have been better to just let users handle object lifetime. But if users
start getting complex SegFaults and exceptions due to managing object lifetimes themselves, then understanding GC and tuning it is still easier. :-)
Nevertheless, lets jump right into it.

How GC operates
===============
A GC works by periodically scanning the Java heap and finding out all the references on the heap which are reachable from the application code.
Then all other references which are not reachable are presumed to be garbage and will be cleaned up by GC. But a GC needs to do more than just that.
1) It needs to find all references that are reachable
2) Free memory which is occupied by all un-reachable references.
3) Compact the heap to prevent fragmentation of the heap.
Because of these complex tasks, different Garbage Collector algorithms exist in the JVM each with its own implementation and performance overhead.

Also, GC isn't as simple as just reference counting the objects. Think of a singly linked list where each node holds a reference to the next node.
So references still exist and their count is not 0. But what is the head is not reachable?? this means that the whole linked list can be cleaned up
even though reference count is not 0, we still need to perform cleanup.

Mutator (application) vs GC threads
====================================
Application threads are also called mutator threads since they keep mutating java heap space. Also, any JVM will typically run multiple GC threads.

How GC works
============
Any general GC works by splitting the JVM heap space into separate partitions; a "YOUNG GENERATION" & an "OLD GENERATION". The young generation is further split into multiple smaller
spaces called Eden and Survivor spaces. The Eden space occupies the most of the young generation. Objects created are first allocated in the young generation. Slowly as multiple GC cycles run, and they are still references by application code and cannot be collected, they are moved to Survivor spaces in young generation and finally they move to old generation.

Typically, a lot of objects in Java are only created for a short duration of time. So JVM periodically tries to cleanup these short lived objects by only running JVM on the Young generation. Any references which are still usable, are moved out of eden space into one of the survivor spaces; and unused references are cleaned up. Eventually, after the end of this GC cycle, Eden and one survivor space is completely freed up and all used references are moved to the second survivor space or to old generation. This GC cycle is called a minor GC or a young GC. Benefits are:
1) The GC will pause the application threads for a very short duration as only young generation needs cleanup. But minor GC pauses will be much more frequent than full GC cycles.
2) The Eden and survivor space are automatically compacted as they are completely free.

As old generation fills up, JVM will need to run the full GC to cleanup the old generation. This is where most of the GC algorithms differ in performance. A lot of collectors will pause the application and perform full GC cycle. But there are some GC alorithms that do not really pause all application threads and can run concurrently. Example: G1 GC.
When running a concurrent GC, application will experience fewer pauses.
1) If you have extra CPU available, you can use concurrent GC. This will avoid full GC pauses and will allow the application to finish faster.
2) If CPU is limited, the extra CPU consumption of the concurrent GC will cause the application to take more time.
So enable concurrent GC when you have extra CPU available.

Different Collectors available
===============================

Serial GC 
---------
1) Default GC on single core machines and 32 bit JVM's.
2) Also default GC in virtual machines or docker containers with single core (with or without hyperthreading)
3) explicitly enable it by using -XX:+UseSerialGC. Cannot disable it by using -XX:-UseSerialGC. Will be disabled by specifying another collector on the command line.
4) Use a single thread for both minor and full GC.
5) Both minor and full GC implementations are stop the world implementations.

Parallel GC 
-----------
1) Default GC on multicore machines and 64 bit JVM's (in JDK 8)
2) explicitly enable it by using -XX:+UseParallelGC. Cannot disable it by using -XX:-UseParallelGC. Will be disabled by specifying another collector on the command line.
3) Uses multiple parallel threads for both minor and full GC. That's why its name is parallel or throughput GC.
4) Both minor and full GC implementations are stop the world implementations.

GI GC 
-----
1) G1 means Garbage first.
2) Default GC on multicore machines and 64 bit JVM's (in JDK 11)
3) explicitly enable it by using -XX:+UseG1GC. Cannot disable it by using -XX:-UseG1GC. Will be disabled by specifying another collector on the command line.
4) It works by dividing the JVM heap space into multiple regions. It is already aware of Young and Old generations. So its own internal regions can fall into either of the 2 generations.
5) When cleaning up its regions which fall into the young generation, it still uses multiple background threads which stop the application thread. So basically minor GC is still 
stop the world.
6) When cleaning up regions which fall in old generation, it processes a region by copying reachable or used references to another region thereby compacting (only partially though) the heap.
7) Remember to use it only when you have extra CPU available; because G1GC threads need CPU.

CMS GC 
------
1) Concurrent Mark and Sweep GC.
2) Was supposed to be a concurrent GC.
3) Now deprecated in JDK 11 and above. Discouraged to use in JDK 8 also.
4) Could not compact the heap without pausing application threads so actually was not good as a concurrent GC

Which GC to use when
====================
deciding which GC to use is a function of:
1) Single or multi CPU system? (SerialGC for Single core, ParallelGC or G1GC for multi CPU)
2) Available CPU's for G1GC to run concurrently with application threads (or otherwise G1GC will start competing with application threads).
3) Number of application threads you are running? (will some CPU cores be available for G1GC)
4) Is your application CPU bound or I/O bound? if CPU bound, (G1GC may be better as it can utilize available CPU cycles).
5) How is your heap occupied? is Old generation full most of the time? Does young generation fill very often etc? (if full GC cycles will be almost 0, then ParallelGC and G1GC may have similar performance)

GC Tuning
=========
1) The first thing to consider while considering GC tuning is the size of the Java heap. JVM provides two arguments -Xms N and -Xmx N, to set the InitialHeapSize and the MaximumHeapSize of the Java heap for an application. 
2) By default Initial and Maximum heap sizes are ergonomically determined by JVM depending on available resources.
3) As a rule of thumb, you should never set the maximum heap size larger than the available physical memory on the host. Or if there are multiple JVM's, the total maximum heap size should be well under the available physical memory. Otherwise, the OS will need to do frequent disk swapping to store inactive pages to disk and to load active/references pages from disk to memory.
4) Also note that JVM uses more memory than just the heap. For example JVM native memory is used to allocate Java methods, thread stacks and native handles as well as JVM's internal data structures. Plus some memory is used for other processes as well. So always factor for all those things when deciding values for -Xmx

How heap grows
==============
JVM heap will grow based on your GC performance goals. You can always specify your GC performance goals on the command line, like:
1) How many GC pauses are you willing to tolerate?
2) The percentage of time you want to spend in the GC. and so on.
Based on these goals, if GC thinks it is doing too much GC, it will expand the heap size upto a max of -Xmx value.

How much heap is sufficient
===========================
As a general rule, your heap should only be about 30% full after a full GC cycle. So you can always use jconsole to connect to your JVM at peak usage time. Then trigger a full GC, 
and observe how much space is occupied after the GC cycle. It should be approx 30%.

Adjusting generation sizes
==========================
1) JVM only provides flags to adjust the size of the young generation. Whatever is left from the total heap size after adjusting the size of the young generation, is given to the old generation.
2) JVM provides a flag -XX:NewRatio=N (default for N = 2). this N is put in the formula:
    YoungGeneration InitialSize = (Initial JVM Heap Size) / ( 1 + N) --> to get the Initial size of the Young generation.
	So default is 33% of JVM heap size for Young generation.
	
	YoungGeneration MaxSize = (Maximum JVM Heap Size) / ( 1 + N) --> to get the Maximum size of the Young generation.
3) To explicitly set Initial and Maximum heap size for young generation, use the -XX:NewSize=N and -XX:MaxNewSize=N flags, or use -Xmn N (if both Initial and Max sizes are same)
4) It is recommended to use NewRatio instead of NewSize/MaxNewSize, because it is easier for the JVM to calculate.
5) By default, as JVM adjust the heap size to meet the GC performance goals, the generation sizes will also be adjusted when minor or full GC's run. The adjustments happen so JVM can reach its GC performance goals. the -XX:+UseAdaptiveSizePolicy is ON by default to adjust the generation sizes. You don't need to disable it unless you have fine-tuned the generation sizes yourself.
6) Use -XX:+PrintAdaptiveSizePolicy flag. Using it, GC logs will print out how the generation sizes are adjusted when GC happens.

Metaspace (previously permgen)
=============================
1) Metaspace is another memory inside your Java application that is used by the JVM to manage class metadata i.e. information on loaded class files etc.
2) It does not store the actual Class objects or reflections objects like Method etc. Just some internal class metadata for use by JVM internally.
3) It has a default Initial size and can grow dynamically. The two JVM flags are -XX:MetaspaceSize=N and -XX:MaxMetaspaceSize=N.
4) You will hardly need to tweak it as default values should be enough. If really your Metaspace is getting filled up, you need to check the reason why instead of just increasing the max metaspace size.
5) Resizing Metaspace requires a full GC, so if your application is doing many full GC's during startup, consider checking this value.

-XX:ParallelGCThreads=N
=======================
This flag controls the number of threads used by ParallelGC and G1GC.
1) For collection of young generation for both ParallelGC and G1GC, this values applies.
2) For collection of old generation for ParallelGC, this values applies.
3) For stop-the-world phases of G1GC, this value applies too.
4) This flag does not apply to the number of background threads used by G1GC.
5) Default value set by JVM is 
    a) 1 thread for each core available on the system. Upto a maximum of 8.
	b) if core count > 8, then for the rest of the cores, 1 thread for every 1.6 cores.
	So if a system has 16 cores, you will have:
	 8 + (16-8)/1.6 = 8 + 5 = 13 threads.
6) Need to choose wisely when you have:
  a) more than one JVM's running on the host and all want to run GC (eg: 4 JVM's running on 16 CPU machine wanting to run GC. you will have 13 * 4 = 52 threads)
  b) heap size is too small and default thread count will be too big (eg 1GB heap on 128 CPU machine)
  c) 4 JVMs running on 16 core machine will require 13 threads for one GC by default. What if your application has more than 4 threads. So your 13 GC threads will compete with 12 application threads in the other 3 VM's
  
Enabling GC Logging
====================
GC Logging enabling is different between JDK 8 and later JDK's.

JDK 8
-----
1) we have two types of GC Logging. Simple logging and detailed logging.
2) Enable simple logging using -XX:+PrintGC or -verbose:gc (disabled by default)
3) Enable detailed logging using -XX:+PrintGCDetails (disabled by default)
4) To display timestamps or datestamps (recommended), use flags: -XX:+PrintGCTimeStamps and -XX:+PrintGCDateDtamps
5) By default, GC logging goes to standard output. To redirect to a file, use flag -Xloggc:<FileName>. Also recommended is to use GC log file rotation using flags:
    a) -XX:+UseGCLogFileRotation
	b) -XX:NumberOfGCLogFiles=N
	c) -XX:GCLogFileSize=N (eg N = 8m means 8mb)
So all together you can use: 
-Xloggc:gc.log -XX:+PrintGCTimeStamps -XX:+UseGCLogFileRotation -XX:NumberOfGCLogFiles=8 -XX:GCLogFileSize=8m (This can be used in production system as only simple logging is enabled automatically when we use -Xloggc flag)
 
JDK 11
------
JDK 11 uses the unified logging feature for all logging including gc logging. The syntax is very trivial. example:

java -Xlog:gc*:filename=gc.log:time:filesize=8m,filecount=7
if you run "java -Xlog:help" you can see the meaning of all the four sections above between the colons (selections, output, decorators, output-options)

-XX:+PrintTenuringDistribution (JDK 8)
--------------------------------------
To enable GC logging to also print tenuring related information, like sizes of survivor spaces and current tenuring threshold values.
Add "age*=debug or age*=trace" to -Xlog for JDK 11

No good tools exist in open source to parse these gc log files. So find out later by google what is the best way. For live monitoring of java heap, use a combination of
1) jvisualvm
2) jconsole
3) jstat

jstat
=====
A very useful option in jstat is "-gcutil" which display over time many things like how many times GC is run, how much time is spent, the heap% occupied etc.
Example to run is : "jstat -gcutil <procesID> <TimeInMillis>" --> jstat will repeat the command every TimeInMilllis milliseconds.