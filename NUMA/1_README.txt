NUMA stands for Non Unified Memory Access
It is a memory design choice available for multiprocessor system. the goals of hardware manufactures are:

1) Scalability - Means the proportionate increase in parallel speedup with increase in multiprocessors. If adding a new core increases gives you twice the speed, your system is highly scalable. However, this is not normally what happens.

2) Latency - Latency is the time in which Node A sends a message to Node B.

3) Bandwidth - This is the amount of data that can be communicated per unit of time.

As a hardware manufacture, your goal is to have High Scalable, Low Latency and High Bandwidth systems.


In multiprocessor architectures, there are two types of memory architectures
1) Shared Memory Architecture - In a shared memory architecture - all processors share the same memory, and this main memory is treated like a global address space. the main issue in SMA is that of Cache Coherency ie (a read should always reflect the latest write).

2) Distributed Memory Archicture - In Which each processor has its own local memory and there is no sharing of memory across processors. So, we don’t have any concept of global address space or cache coherency. To access data in another processor, processors use explicit communication (like communication over a network). One example where this architecture is used is clusters, with different nodes connected over the internet as network. You remember using SLURM in DRW. That's an example of Distributed Memory Architecture.


