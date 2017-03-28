See UMA_FSB.png

The figure shows an example architecture of an UMA system. All CPU's connect to a memory controller hub through a Front Side Bus (FSB).
To access memory, CPU's need to go through the MCH. Also the I/O Controller Hub is connected to MCH as I/O devices will also need to access memory.

As you can see, such systems have to get control of the FSB to access memory, so the Bus becomes a bottleneck and can cause contention problems.
