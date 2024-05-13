Chronicle map is an in memory key-value store
 1) It is designed for low-latency.
 2) It is super-fast.
 3) It can be concurrently accessed by multiple processes, even by processes across a network using replication.
 4) key-value store is persisted to disk
 5) At the core, a chronicle map data store is a big chunk of shared memory.

How it works?
 1) It uses off-heap memory to store the data (i.e. it doesn't use the Java heap).
 2) It uses a custom serialization/deserialization logic to store the data.
 3) It uses memory-mapped files to persist the data to disk.
 4) It uses a custom replication protocol to replicate the data across machines.

It is a drop-in replacement for ConcurrentHashMap, and can also be a replacement for Redis, Memcached etc.

The Chronicle map shared memory is split into multiple independent memory segments, each of which is a separate file on disk. Each segment has:
1) a separate area for storing the entries
2) a hash table for indexing the entries for search
3) a lock in shared memory (implemented using CAS atomic operations)

Let's play with it. Please see ChronicleMapInMemory.java