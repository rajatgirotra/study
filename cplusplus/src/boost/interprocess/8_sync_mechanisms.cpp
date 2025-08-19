/*
 * boost interprocess implements a number of synchronization mechanisms. these are:
 *
 * mutex
 * semaphores
 * condition variables
 * file locks
 * message queues
 * etc.
 *
 * They fall in one of the two categories
 * 1) Named: which means they will be visible in the filesystem somewhere. They will have kernel persistence. Multiple processes will create
 *    objects for this mechanism based on name of the mechanism, but they all will refer to the same underlying mechanism.
 * 2) Anonymous: these mechanism can only be created on a mappable_object like shared memory or memory mapped file. They have advantage that
 *    they can be persisted on disk on re-used after a system reboot. All processes will share the same object persisted on the mappable object.
 *
 *  most of the mechanisms are in boost/interprocess/sync/... folder
 *  Mutex classes:
 *  =============
 *  interprocess_mutex : Anonymous mutex, can be persisted on shared memory or memory mapped file.
 *  interprocess_recursive_mutex: same as above but recursive.
 *  named_mutex: a named mutex
 *  recursive_named_mutex: same as above, but recursive
 *  shareable_mutex: kind of read write lock. provides interface for taking shared_lock() or exclusive_lock()
 *  upgradeable_mutex: same as sharable_mutex. But a shared_lock() can be upgraded to exclusive_lock()
 *  scoped_lock<>: helper class which provides RAII wrapper for mutex classes.
 *  sharable_lock<>: helper class which provides RAII wrapper for shareable mutex classes (ie shareable_mutex and upgradeable_mutex)
 *
 *
 *  Condition Variables classes
 *  ===========================
 *  interprocess_condition: Anonymous condition variable
 *  interprocess_condition_any: Anonymous condition variable
 *  named_condition: named condition variable
 *  named_condition_any:
 *
 *
 *  Semaphores (basically provides Wait and Post)
 *  ============================================
 *  Wait --> will test if semaphore count <= 0. If yes, will block, otherwise will decrement count and proceed.
 *  Post --> will increase semaphore count. If any processes is stopped, it will be woken up.
 *  We have:
 *  interprocess_semaphore
 *  named_semaphore
 *
 *  File Locking
 *  ============
 *  A file lock is used to provide a synchronization mechanism for reading and writing to files in a consistent manner.
 *  When you create an instance of boost::interprocess:file_lock you must specify the file name you want to read/write and
 *  a mutex for that file access is automatically created. The mutex provides a sharable_mutex type of interface.
 *  Also, this lock has process persistence; if the process crashes, the lock is automatically released.
 *  Caution:
 *  It's unspecified if a file_lock synchronizes two threads from the same process. (so only use for inter process locking, not intra-process locking).
 *  It's unspecified if a process can use two file_lock objects pointing to the same file.
 *
 *  Also, with iostreams, always use flush() function to send all data to files before releasing the lock.
 *
 *  Message Queues
 *  ==============
 *  A named queue object that can be used to send data from one side and read from the other side. data is sent as a stream of bytes.
 *  so it must be serializable. Boost message queue is unlike Unix message queues, as Unix MQ's have structure to the data that is sent.
 *  in case of Boost MQ's we send as series of bytes. So looks like Boost MQ are like Unix pipes.
 *  messages can also have a priority and receiver can read out of order based on priority. receiver can do blocking receive or try_receive
 *  or timed_receive.
 */