Advanced Tuning Flags
=====================

-XX:InitialTenuringThreshold=N & -XX:MaxTenuringThreshold=N
-----------------------------------------------------------
What is the use of the survivor space? Why do we have two survivor spaces, S0 and S1?
When a young generation is collected, not all live objects should be promoted to old generation. As some live objects may still be short lived and collected in the next 2-3 young collections. So JVM promotoes few live objects to S0 in the first collection. In the second collection, the Eden and S0 spaces are collected, and live objects move to S1. This is repeated again and live objects move to S0 in the third collection. This keeps repeating; however this can not go on endlessly. The number of GC cycles during which objects can live in the Survivor spaces is called the Tenuring threshold. Default initial value of tenuring threshold is 7 for both ParallelGC and G1GC and can be changed using the InitialTenuringThreshold flag. Similarly default max value is 15 for both GC's. 
JVM will keep adjusting the value of this threshold between 1 and the MaxTenuringThreshold dynamically.

-XX:InitialSurvivorRatio=N & -XX:MinSurvivorRatio
-------------------------------------------------
Though JVM will dynamically keep changing the size of the survivor spaces based on the TargetSurvivorRatio flag (see next section); you can still set an Initial and Max value based on the size of the Young generation.

survivor_space_initial_size = (young_generation_size)/ (InitialSurvivorRatio + 2). Default for InitialSurvivorRatio is 8, i.e. each of S0 and S1 is 10% of young generation size.
survivor_space_max_size = (young_generation_size)/ (MinSurvivorRatio + 2). Default for MinSurvivorRatio is 3, i.e. each of S0 and S1 is 20% (1/5th) of young generation size.

-XX:TargetSurvivorRatio=N
-------------------------
JVM uses this flag to set S0 and S1 sizes. after each GC is run, JVM will check the available space in S0 or S1. S0 and S1 are resized, so that they are atleast N% full. Default for N is 50.

-XX:+AlwaysTenure
-----------------
Enabling this tells the JVM to directly promote live objects from Eden to old generation; without promoting to survivor space.

-XX:+NeverTenure
-----------------
Enabling this tells the JVM to ignore the tenuring threshold and keep live objects in S0 or S1 as long as there is survivor space available. If no more survivor space is left,
then promote to old generation.

TLAB
====
Applications that allocate a lot of large objects may need to tune the TLABs (though often using smaller objects in the application is a better approach). But what is TLAB?
TLAB stands for Thread Local Allocation Buffer. You would have already read that allocating objects in the Eden space is faster. The reason is that every thread gets its own area of some size called the TLAB. Each thread will use its own TLAB to allocate objects so no synchronization is required. Hence allocation is faster. Let say now that a TLAB of size 100KB is 75KB full and a new object needs to be allocated of size 30KB. In that case, JVM can take two appoaches.
1) JVM can allocate 30KB on the heap outside the TLAB. and still keep using the TLAB for any future requests that are within 25KB size
2) JVM can retire the TLAB and create a new TLAB for future requests. So now the 25KB of space in the first TLAB is wasted.

There are flags -XX:TLABWasteTargetPercent=N and -XX:TLABWasteIncrement=N which can be used to decide which apporach (1 or 2 above) JVM should take. I will not discuss those in detail for now. But only later if we need it.

TLAB boosts performance and disabling it is almost always a bad idea. You can still disable it using -XX:-UseTLAB.

To pin the TLAB size, you must:
1) Set -XX:TLABSize=N flag. By default, the value of the flag is 0 which means TLAB size is dynamically set by JVM.
2) Also disable resizing of TLAB explicitly using -XX:-ResizeTLAB at the end of each GC cycle.

If you see that a lot of objects are getting allocated outside the TLAB, then may be you need some tuning. The best tool to view TLAB usage is JFR (Java Flight Recorder).
Outside of the JFR, you can add "-XX:+PrintTLAB" (for JDK8) or "tlab*=trace" (for JDK 11) 

Minimum size of TLAB can be changed using -XX:MinTLABSize=N, but maximum size is just under 1GB and cannot be altered.

G1GC Region Size
================
You know already G1GC divides the heap space into regions. The region size is dynamically determined at JVM startup based on the size of the java heap. There is a table which tells you the size of the G1 region size based on the JVM heap size. It must be a power of 2. You can specify a size yourself using -XX:G1HeapRegionSize=N flag but you would only need to this when you are dealing with Humongous objects