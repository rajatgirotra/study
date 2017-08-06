/*
Very simple RAII wrapper over Mutex. The c'tor calls lock() and the d'tor calls unlock() on the mutex.

std::lock_guard(std::mutex) --> This c'tor calls lock()
std::lock_guard(std::mutex, std::adopt_lock_t) --> This doesnt call lock(). std::adopt_lock_t is nothing more than a tag to tell the user that it is a different c'tor which doesnt call lock(). The d'tor is going to call unlock() anyway, so the responsibility is on the user to lock() the mutex explicitly.

its neither copyable nor movable obviously as the underlying mutex is not copyable and movable.

template <typename Mutex>
struct lock_guard {
    Mutex& m;
    std::lock_guard(Mutex& p) : m(p) {
        m.lock();
    }

    std::lock_guard(Mutex& p, std::adopt_lock_t) : m(p) {}

    ~lock_guard() {
         m.unlock();
     }
};

*/
