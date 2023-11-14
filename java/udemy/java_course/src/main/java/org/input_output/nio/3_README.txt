File Locking
============

lock/trylock
------------
FileChannel provides an overloaded tryLock() api to lock a file for shared or exclusive access. This lock is held on behalf of the whole JVM, so it is not suitable
to be used across threads in the same process.

FileLock tryLock() --> with no arguments by attempt to lock the whole file. Will return immediately. If lock is acquired, FileLock returned is non-NULL, otherwise
null is returned. this function can throw some IOException.

FileLock tryLock(position, size, shared) --> To lock a region of a file. the argument shared is set to true, when you want a shared lock, otherwise set it to false
for exclusive lock.

Lock regions are fixed in size; if a locked region initially contains the end of the file and the file grows beyond the region then the new portion of the file will
 not be covered by the lock.

Similarly, an overloaded lock() api is also available for acquiring exclusive locks.

A lock held by JVM will be seen by other JVM and native processes also.

release
--------
locks are released by calling FileLock.release() method.

isShared
--------
Support for exclusive or shared locks must be provided by the underlying operating system. If the operating system does not support shared locks and a request is
 made for one, an exclusive lock is used instead. The type of lock (shared or exclusive) can be queried using FileLock.isShared().

YOU CANNOT ACQUIRE A LOCK ON A BUFFER. YOU CAN ONLY GET A FILE LOCK ON THE CHANNEL.

Read LockingMappedFiles.java next