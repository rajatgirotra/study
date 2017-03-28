There are many different types of NUMA architectures possible:
These days we have systems with 2, 4, and upto 8 sockets.
and 2 to 10 sockets per core. So we can have upt0 8 * 10 = 80 cores or 160 cores with hyperthreading.

Given that there are multiple types of NUMA architectures possible, it unfortunately becomes very important to have some information on the network
topology of your production system, to write low latency code which is best suited for that architecture.
On ubuntu you can do:
bash$> sudo apt-get install hwloc
bash$> lstopo
lstopo is a command which brings up a graphical image of your systems underlying topology. If not running X, it will output text.

What is a NUMA node or NUMA domain..

A numa node is a combination of one or more cores on a socket together with the portion of memory which is directly attached to it.

For example, a sample Sandy Bridge architecture has:

1) 32 GB of total RAM
2) 16 total cores
3) 2 sockets (8 cores per socket)
4) Each core has its own 32 KB of L1 cache, 256 KB of L2 cache and 20MB of L3 shared between all cores on the same socket.

It has two NUMA nodes each having
1) 16GB of RAM
2) One socket (ie 8 cores)

So if a processor has to access memory in an another NUMA domain, it will have to pay huge access penalty.
Also to commincate b/w sockets, Intel has what you call as QPI (or quick path interconnect), AMD has Hypertransport
