AMPS (Advanced Message Processing System) is a messaging middleware built with the following design goals.
1. Low latency
2. High throughput
3. scalable (distributed)
4. high availability/fault-tolerant (using replication)

What are the various components in AMPS?
========================================
1. Fast messaging engine - supports both publish-subscribe model of messaging and queue based message delivery. It allows you to subscribe to messages in queue based on Topics or even content based filtering. Content based filtering eliminates the need for topics.

2. AMPS also provides an integrated database that applications can use as a simple/basic cache, or either a key/value document store or a fully queryable database - or even all of this at the same time.

3. AMPS provides an aggregation or analytics engine for real time analysis of streaming data, including aggregation across multiple topics or message formats.

Other good features
===================
1. There is integrated logging so you can record and replay streams of messages.
2. High availability features - AMPS provides replication and automatic failover and recovery of applications.
3. A rest interface to monitor statistics and collect data which can be fed into other monitoring and observability systems.
3. Authentication and entitlement support.

AMPS transaction log
====================
AMPS uses a message store for replication which is called the AMPS transaction log. Same transaction log is also used for durable subscriptions,message replay and replicating messages between multiple AMPS instances.

More details
============
1. Topic names can include regular expressions.
2. For content based filtering, you can specify filter using XPath identifiers (can include regular expressions).
3. It can understand many message formats out of the box like Google Protobuf, Json, XML, FIX protocol, NVFIX(i.e. name/value FIX instead of tag value), MessagePack, BSON etc.
4. Client libraries in C/C++, Java, .NET, Python, Go, Javascript