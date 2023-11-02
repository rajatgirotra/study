How the Parallel (i.e. Throughput) collector works
==================================================
To understand how ParallelGC works, we have to look through its log files. ParallelGC does all three things (search unusable objects, free memory, compact heap) in a single GC cycle;
whether it is the minor or full GC. Lets see a sample JDK 8 log of minor/young GC.

17.806: [GC (Allocation Failure) [PSYoungGen: 227983K->14463K(264128K)] # shows that YoungGC allocation changed frp, 227MB to only 14MB. and the total size of the Young generation now is 264 MB (i.e. eden + 2 survivor spaces)
280122K->66610K(613696K), 0.0169320 secs] # shows that the total heap size allocation (young+old generation) changed from 280MB to 66MB and the total heap size now is 613MB.
[Times: user=0.05 sys=0.00, real=0.02 secs] # young GC took 0.02 secs (i.e. 0.1699320 secs rounded). user time is 0.05 as multiple threads performed the YoungGC

JDK 11 log is also similar. Just that they also how the metaspace allocation.

Similarly, a full GC log looks like this:

64.546: [Full GC (Ergonomics) [PSYoungGen: 15808K->0K(339456K)]
[ParOldGen: 457753K->392528K(554432K)] 473561K->392528K(893888K)
[Metaspace: 56728K->56728K(115392K)], 1.3367080 secs]
[Times: user=4.44 sys=0.01, real=1.34 secs]

Adaptive vs Static Heap Sizing
-------------------------------
By default, in JVM, adaptive heap sizing is enabled; which means JVM will increase/shrink the size of the JVM heap and also fine tune the sizes of the young and old generation to meet the Parallel GC collector goals. But what are these goals??
There are two main goals of the ParallelGC.

1) Pause-time goal: 
   a) Controlled by JVM flag, -XX:MaxGCPauseMillis=N
   b) you tell JVM how much millis you are willing to wait for every GC cycle. This value applies to both youngGC an fullGC.
   c) by default, in JVM this goal is not set. The Throughput goal below is set.
   d) setting this value to very low value like 50ms would mean JVM needs to allocate very little heap space for old generation. Basically, something that it can clean up in 50ms.
      This will result in twoo frequent full GC cycles, resulting in dismal performance, so be realistic.
   e) If both Pause-time and Throughput goals are set, then this goal takes precedence.
   
2) Throughput goal or the time-ratio goal:
   a) Controlled by JVM flag, -XX:GCTimeRatio
   b) Basically tells JVM what percentage of time are you willing to sacrifice for running GC. All the rest of the time, the application threads should run.
   c) GCETimeRatio = (ThroughPut) / (1-ThroughPut). If you want application threads to run 99% of the time, set ThroughPut to 99 and calculate the GCTimeRatio.
      Example: GCTimeRatio = 0.99/(1-0.99) = 99, with 95% application time and 5% GC time, GCTimeRatio = 0.95/(1-0.95) = 19
   d) Default for this flag is 99%.

The JVM uses these two flags to set the size of the heap within the boundaries established by the initial (-Xms) and maximum (-Xmx) heap sizes. The MaxGCPauseMillis flag takes precedence: if it is set, the sizes of the young and old generations are adjusted until the pause-time goal is met. Once that happens, the overall size of the heap is increased until the time-ratio goal is met.

For a fixed size heap, set the -Xms and -Xmx parameters equal to each other. But Adaptive sizing is preferred. Use fixed size heaps only after thorough fine tuning.

How the G1GC collector works
============================
G1GC working is a bit complex but i will try to explain. G1GC has four logical operations:

1) A young collection operation (This is stop the world operation)
2) A concurrent marking operation (has many phases, some phases are stop the world, some phases are concurrent)
3) A mixed collection operation.
4) If required, a full GC operation.

G1GC operates by dividing the heap size into regions. Lets say it internally divides the heap space into 2000 small regions. It then marks each region as 
1) S meaning survivor space
2) E meaning Eden space
3) O meaning old generation space
4) <Nothing> : regions which are not occupied at all. 

Young collection operation
---------------------------
1) When all the Eden regions are filled up, the young collection starts.
1) This will stop all application threads.
2) Free up all unreachable references in eden regions.
3) promote used/reachable references to either survivor space or old generation.
4) empty Eden regions are remembered by G1GC as those spaces will again start filling up when application threads start again.

Concurrent marking operation
----------------------------
This can be broken down into multiple phases
1) initial-mark (JDK8) or concurrent-start(JDK 11)
  a. This phase stops all application threads partly (partly means only for some duration).
  b. It runs the young collection. (which requires all application threads to be stopped).
  c. Then sets up the next phase.
Logs in JDK 8:
50.541: [GC pause (G1 Evacuation pause) (young) (initial-mark), 0.27767100 secs]  # the initial-mark log message tells you that the concurrent marking operation has started.
... lots of other data ...
[Eden: 1220M(1220M)->0B(1220M)
Survivors: 144M->144M Heap: 3242M(4096M)->2093M(4096M)]
[Times: user=1.02 sys=0.04, real=0.28 secs]

Logs in JDK 11:
[50.261s][info ][gc,start ] GC(11) Pause Young (Concurrent Start) # the concurrent-start log message tells you that the concurrent marking operation has started.
(G1 Evacuation Pause)
[50.261s][info ][gc,task ] GC(11) Using 4 workers of 4 for evacuation
[50.541s][info ][gc,phases ] GC(11) Pre Evacuate Collection Set: 0.1ms
[50.541s][info ][gc,phases ] GC(11) Evacuate Collection Set: 25.9ms
[50.541s][info ][gc,phases ] GC(11) Post Evacuate Collection Set: 1.7ms
[50.541s][info ][gc,phases ] GC(11) Other: 0.2ms
[50.541s][info ][gc,heap ] GC(11) Eden regions: 1220->0(1220)
[50.541s][info ][gc,heap ] GC(11) Survivor regions: 144->144(144)
[50.541s][info ][gc,heap ] GC(11) Old regions: 1875->1946
[50.541s][info ][gc,heap ] GC(11) Humongous regions: 3->3
[50.541s][info ][gc,metaspace ] GC(11) Metaspace: 52261K->52261K(1099776K)
[50.541s][info ][gc ] GC(11) Pause Young (Concurrent Start)
(G1 Evacuation Pause)
1220M->0B(1220M) 280.055ms
[50.541s][info ][gc,cpu ] GC(11) User=1.02s Sys=0.04s Real=0.28s

2) concurrent-root-region-scan phase
  a. This stage doesnt require to stop all application threads. 
  b. Background threads work concurrently alongside application threads.
  c. The phase cannot be interrupted by the Young collection. If Eden space fills up during this phase, the Young Collection will need to wait.
  d.
  
3) concurrent-mark-start
   a. This stage doesnt require to stop all application threads. 
   b. Background threads work concurrently alongside application threads.
   c. The phase CAN BE interrupted by the Young collection. so young collections may occur during this phase.
   
4) The marking phase is followed by a remarking phase and a normal cleanup phase
	120.910: [GC remark 120.959:
	[GC ref-PRC, 0.0000890 secs], 0.0718990 secs]
	[Times: user=0.23 sys=0.01, real=0.08 secs]
	120.985: [GC cleanup 3510M->3434M(4096M), 0.0111040 secs]
	[Times: user=0.04 sys=0.00, real=0.01 secs]
These phases stop the application threads, though usually for a short time.

5) concurrent-cleanup
 and lastly an additional cleanup phase happens concurrently.
 And with that, the normal G1 GC background marking cycle is complete
 
very little has actually been freed yet. A little memory was reclaimed in the cleanup phase, but all G1GC has really done at this point is to identify old regions that are mostly garbage and can be reclaimed. By the end of concurrent marking phase:

--> the young generation has changed its occupancy: there will be at least one (and possibly more) young collections during the concurrent cycle. Hence, the eden regions
before the marking cycle have been completely freed, and new eden regions have started to be allocated.

--> some regions are now marked with an X. Those regions belong to the old generation (and note that they still contain data)— they are regions that the marking cycle has determined contain mostly garbage.

--> Finally, notice that the old generation (consisting of the regions marked with an O or an X) is actually more occupied after the cycle has completed. That’s because the young generation collections that occurred during the marking cycle promoted data into the old generation. In addition, the marking cycle doesn’t actually free any data in the old generation: it merely identifies regions that are mostly garbage. Data from those regions is freed in a later cycle.



mixed collection operation
==========================
After the concurrent marking operation, a series of mixed GCs is run.
1. It's called mixed because both young collection and the old generation garbage regions marked 'X' are cleaned up.
2. If an almost garbage region 'X' is freed up, the live objects in that region are moved to another region in the old generation. This leads to automatic compaction.
3. Note that each mixed GC cycle may remove only few of the targeted regions marked 'X' of the old generation.
4. These mixed GC cycles will continue until all the marked regions have been collected. Default is 8 cycles (governed by -XX:G1MixedGCCountTarget=N flag)
5. G1GC cannot start another concurrent mark cycle until all the marked regions are collected. Once done it can then start another concurrent cycle or it can start with a normal
   Young collection operation.
Example log:
	The mixed GC operation usually looks like this in the log:
	79.826: [GC pause (mixed), 0.26161600 secs]  # in JDK 11, it will show as "prepared mixed" instead of "mixed"
	....
	[Eden: 1222M(1222M)->0B(1220M)
	Survivors: 142M->144M Heap: 3200M(4096M)->1964M(4096M)]
	[Times: user=1.01 sys=0.00, real=0.26 secs]
	[3.800s][info][gc,start ] GC(24) Pause Young (Mixed) (G1 Evacuation Pause)
	[3.800s][info][gc,task ] GC(24) Using 4 workers of 4 for evacuation
	[3.800s][info][gc,phases ] GC(24) Pre Evacuate Collection Set: 0.2ms
	[3.825s][info][gc,phases ] GC(24) Evacuate Collection Set: 250.3ms
	[3.826s][info][gc,phases ] GC(24) Post Evacuate Collection Set: 0.3ms
	[3.826s][info][gc,phases ] GC(24) Other: 0.4ms
	[3.826s][info][gc,heap ] GC(24) Eden regions: 1222->0(1220)
	[3.826s][info][gc,heap ] GC(24) Survivor regions: 142->144(144)
	[3.826s][info][gc,heap ] GC(24) Old regions: 1834->1820
	
Full GC operation
=================
Triggered only under certain circumstances. If this is triggered, it usually suggests that you need to further tune your GC settings to improve application performance.
What are those circumstances really?

Concurrent mode Failure
-------------------------
Lets say the concurrent marking phase is running and the old generation fills up even before the phase is completed. JVM will abort the phase and run a full GC. concurrent mode
failure suggests that:
  a) either the heap size should be increased.
  b) this phase should have started sooner.
  c) this phase should have run faster by tuning the parameters.

promotion failure
------------------
This happens when the mixed GC is running and the young collection promotes too many objects to old generation filling it up. This will cause a full GC. This suggests that
mixed GC must happen more quickly.

evacuation failure
------------------
Same as above but happens in normal young collection operation when too many objects are promoted to survivor and old generation but there isn't enough free space available
in those regions. This results in full GC.

metaspace failure
-----------------
if metaspace needs to be expanded. it will result in full GC.

Humongous allocation failure
----------------------------
When you allocate objects of very big sizes, it can also result in full GC.

Tuning G1GC
===========
The main goal of tuning G1GC is to make sure these failures above don't occur often, specially the concurrent mode or evacuation failures. Also tuning requires to make sure
Young collection doesn't have to wait for "concurrent-root-region-scan" phase of the concurrent marking operation.
Also, it is important to tune G1GC properly in JDK8 as full GC works on single thread in JDK8. in JDK11, it works on multiple threads based on -XX:ParallelGCThreads=N setting.

G1GC attempte to keep tuning parameters to a minimum. So it provides a "Pause-time" performance goal parameter; similar to the one in ParallelGC. It is called by the same name:
-XX:MaxGCPauseMillis=N. However unlike ParallelGC where it doesnt have a default, for G1GC it has a default value of 200ms. This one value will try to optimize G1GC for all of the below settings:

--> Increase the size of the old generation either by increasing the heap space overall or by adjusting the ratio between the generations.
--> Increase the number of background threads (assuming there is sufficient CPU).
--> Perform G1GC background activities more frequently. 
--> Increase the amount of work done in mixed GC cycles.

More fine tuning can be achieved by the following flags.

-XX:ConcGCThreads=N
===================
This flag affects how many background threads should run during the concurrent marking operation. Note that the -XX:ParallelGCThreads=N flag affects the operations which are stop the world. However, -XX:ConcGCThreads=N affects operations which are concurrent.
The default value for the ConcGCThreads flag is defined as follows: ConcGCThreads = (ParallelGCThreads + 2) / 4

-XX:InitiatingHeapOccupancyPercent=N
====================================
N is the percentage of heap occupancy at which G1GC will trigger the concurrent marking cycle. N is a percentage of the entire heap, not just the young or old generation

-XX:G1MixedGCCountTarget=N
==========================
How many max G1GC mixed GC cycles should be run to clear all the 'X' marked regions. Default is 8. reducing it can reduce promotion failures as old generations 'X' marked regions will be cleaned up faster. However the pause time may get longer.