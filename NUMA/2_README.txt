Shared Memory Architectures are further divided intp UMA and NUMA

UMA - In UMA, all processors are identical and have equal access times to all memory regions. These are also called Symmetric Multiprocessor systems. Systems which implement Cache Coherency completely in hardware are called CC-UMA systems (ie Cache Coherant UMA) systems. UMA, however, has a major disadvantage of not being scalable after a number of processors. We'll see later why this is.

NUMA - in NUMA, each processor has a portion of memory attached directly to it. This piece of memory is called (local memory) for that processor and the other portion is called remote memory. The main difference b/w NUMA and DMA design is that a processor in DMA has no mappings to memory connected to other processors. However, in NUMA, a processor may have mappings to remote memory.


