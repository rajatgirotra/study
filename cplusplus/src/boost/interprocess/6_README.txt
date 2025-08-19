IPC mechanisms and persistence.

IPC using files: i.e we have readers and writers processes which read and write to files. This will require some form of manual
synchronization using locks, semaphores etc

IPC using kernel: In this processes share some data in the kernel. Typical example ie message queues. In this case, synchronization
is guaranteed by kernel.

IPC using memory: ie. using shared memory (sysV, posix) or memory mapped files. This will require some form of manual
synchronization using locks, semaphores etc


IPC lifetime:

Process persistence --> the mechanism lives as long as the process is up or until the mechanism is explicitly closed by the process.

kernel persistence --> the mechanism lives as long as the kernel is not re-booted or until the mechanism is explicitly destroyed.
ie. shared memory

Filesystem-persistence --> The mechanism exists until the mechanism is explicitly deleted

Examples:

shared memory --> kernel or filesystem
memory mapped file --> filesystem
process-shared mutex types --> process
process-shared semaphores --> process
process-shared condition variables --> process
file lock --> process
message queue --> kernel or filesystem
named mutex --> kernel or filesystem
named semaphore --> kernel or filesystem
named condition --> kernel or filesystem