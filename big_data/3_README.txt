What are the components of Hadoop

1) HDFS --> Hadoop Distributed File System --> Every node in the hadoop cluster will have its own HDFS. This will be a local file system so that data is available locally (ie readily available) for processing

2) Map --> A map is a single unit of task. that means preparing meat and preparing sauce are two separate tasks. which Hadoop can do parallely.

3) Reduce --> Reduce is the step of building intermediate or final results by getting data from 2 or twore Map units. You can compare Reduce directly to the head-chef who assembles the meat-sauce on the plate. Hence the term MapReduce in Hadoop.


MORE ABOUT Hadoop HDFS
----------------------
Hadoop HDFS is a master/slave architecture. ie. there is one master node called the "NamedNode" and multiple slave nodes called the "DataNode". Every "NamedNode" has two important files
1) fsImage --> this file contains all changes to the hadoop cluster since the named node started. This file can be very big so its maintained on the file-system

2) editLog -->this file contains the latest history for the past 1 hour (configurable). 

Checkpointing
-------------
Hadoop also has a "SecondaryNamedNode" --> This may look like a back up NamedNode if the main one goes down but it is not so. It is used for checkpointing. Every 1 hour (configurable), the main NamedNode will start writing to a new editLog file, and the SecondaryNamedNode will merge the old editLog file with the fsImage to create a new fsImage. This is called Checkpointing.

3) Scalabilty and Fault Tolerant
--------------------------------
The distributed and parallel computing model is obviously scalable. You can quickly add more compute power by adding more nodes. Making the model Fault tolerant is achieved by duplicating the data across several nodes, so that if one node goes down, data can be accessed from another node. We have ditto architecture in ELK also (Elastic search).


More about HDFS
---------------

The Hadoop File System (HDFS) is an open-source file system derived from Google's file system (GFS). However, GFS is proprietary to Google. Hadoop is written in Java, HDFS is really a meta-file system -- in other words, a file system that sits on top of a lower-level file system. It is designed to be fault-tolerant, allowing copies of the data to be stored in various locations within the file system, so recovering from a corrupt copy of the data or a down server is rather easy. Plus these copies can also be used to improve performance.

DataNode - So a datanode is nothing but a server with some storage and networking. Each datanode serves up the data over the network (Ethernet) using a block protocol unique to HDFS. 

NamedNode - Also called the metadata server.

SecondaryNamedNode - used for checkpointing (also called snapshotting the directory information from the primary Namenode to help reduce downtime in the event of a Namenode failure) Regardless, because there is only one Namenode, it can become a potential bottleneck or single point of failure for HDFS.

One of the key features of HDFS is that the data is replicated across multiple datanodes to help with resiliency. By default, HDFS stores three copies of the data on different datanodes. Two copies are within the same rack, and one is on a different rack (i.e., you can lose a rack and still access your data). Jobs will be scheduled to run on a specific datanode that has the required data, so by default it is one of the three datanodes that has a copy of the data (Note: It may be subtle, but the datanodes store data and provide data access while also running jobs).

This is the concept that many people refer to as "moving the job to the data, rather than moving the data to the job." This reduces data movement and also reduces the load on the network because data isn't being moved to run a job. Once the job starts running, all data access is done locally, so there is no striping across datanodes or using multiple data servers for parallel data access. However, large files are stored across multiple machines. The parallelism in Hadoop that can result in performance is achieved at the application level where several copies of the same application may be run, accessing different data sets. Moreover, improved performance can be achieved because you have three copies of the data, so you could potentially run three jobs that require access to the same file at the same time.

In the background, the datanodes will communicate with each other using RPC to perform a number of tasks:

Capacity balance across datanodes while obeying the data replication rules
Compare the files to each other so a corrupted copy of a file is overwritten with a correct copy
Check the number of data copies and make additional copies if necessary
Note that HDFS is not a POSIX compliant file system primarily because the performance can be improved.

Accessing data in HDFS is fairly simple if you use the native Java API, the Thrift API, the command-line interface, or browse through the HDFS-UI webpage over HTTP. Beyond that, directly mounting HDFS on an operating system is not possible. The only solution at the time of this article is to use a Linux FUSE client that allows you to mount the file system.
