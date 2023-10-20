Thread starvation is when a thread doesn't get scheduled at all and keeps waiting too long to get the CPU,
It can happen when you have too many threads in your system waiting for a lock, and when the lock becomes available,
any random thread gets scheduled. But some thread is so unlucky that it never gets scheduled. May be because other threads
have a higher priority to get scheduled by the OS.

Note that setting a thread's priority in Java using Thread.setPriority() is just a request to JVM and OS. It is non-binding.
As a rule of thumb, don't rely on thread priorities at all.

Live lock
=========
A live lock is when two or more threads are running but no useful work is getting done.