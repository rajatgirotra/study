/*
C++11 has std::mutex, std::timed_mutex, std::recursive_mutex, std::recursive_timed_mutex.

std::mutex is very simple synchronization primitive. Its a non recursive mutex.

constexpr std::mutex() noexcept; // c'tor is constexpr, this means if you have global std::mutex objects. and global classes which use the std::mutex, then it is safe to lock the mutex object in the c'tor of the global class. So nice concept to think about.

copy c'tor is deleted: Obviously, this would mean we can have multiple variables (m1, m2, m3)in different threads (t1, t2) etc which would be a great deal of confusion.

move ctor is also deleted: Obvisouly, if thread T1 owns a mutex, and thread T2 moves, it, what will thread T1 unlock???

It is undefined behavior if
1) A mutex object is destroyed while a thread is owning it. OR
2) A thread terminates while owning a mutex.

The std::mutex API is extremely simple, just lock(), unlock() and try_lock(). try_lock() will return true/false.
Remember the behavior is undefined (a deadlock could occur or some other strange behavior) if a thread calls lock() multiple times. Some implementations will throw an std::system_error() indicating that the resource would deadlock, instead of causing a deadlock.

If your class holds an std::mutex, it automatically becomes non-copyable and non-movable.

To enable movability - Wrap your std::mutex inside an std::unique_ptr<std::mutex>. So it becomes moveable. and use std::make_unique() passing the arguments to std::unique_ptr.
To enable copyability - Wrap in std::shared_ptr<std::mutex>, as std::shared_ptr<> is copyable and movable.
If you dont want to share the std::mutex object during copy ctor or assignment, create a new std::mutex instead of using and std::shared_ptr.

NOTE THAT ACCORDING TO THE STANDARD, std::mutex::try_lock() is allowed to fail spuriously even when no other thread is owning the mutex.

AS A RULE OF THUMB NEVER USE raw std::mutex, always use with std::lock_guard, std::unique_lock etc for proper exception handling.

Also many times you would want to make your class member functions const, but cannot because it locks and unlocks a mutex data member. So almost always, you would want to declare your mutex as mutable in your class.
*/
