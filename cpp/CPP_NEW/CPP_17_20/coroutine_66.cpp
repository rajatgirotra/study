/* first coroutine */

#include <iostream>
#include <coroutine>
#include <exception>
using namespace std;

// coroutine interface that the caller of coroutine will use to deal with the coroutine.
// why [[nodiscard]] --> If the caller will not capture the return type, how in the world will he deal with
// the coroutine?  It is basically to catch bugs where developers might accidentally treat coroutines as normal
// functions and ignore their return value.
struct [[nodiscard]] CoroTask {
    struct promise_type;
    using CoroHdl = std::coroutine_handle<promise_type>;
    private:
        CoroHdl m_handle;

    public:
        // ctor and dtor
        explicit CoroTask(auto handle) : m_handle(handle) {}
        ~CoroTask() {
            if(m_handle) {
                m_handle.destroy(); // must always destroy the coroutine frame on memory.
            }
        }    
        
        // disable copy and move to keep things simple
        CoroTask(const CoroTask&) = delete;
        CoroTask(CoroTask&&) = delete;

        bool resume() noexcept {
            // if handle is nullptr of if coroutine has already completed, return false.
            if(!m_handle || m_handle.done()) {
                return false;
            }

            // use the native coroutine API to resume the coroutine.
            m_handle.resume();
            return !m_handle.done();
        }
};

struct CoroTask::promise_type {
    auto get_return_object() {
        return CoroTask{CoroTask::CoroHdl::from_promise(*this)};
    }

    auto initial_suspend() noexcept { return std::suspend_always{}; }
    auto final_suspend() noexcept { return std::suspend_always{}; }

    void unhandled_exception() { std::terminate(); }
    void return_void() {}
};

CoroTask coro(int max) {
    cout << "\tcoro " << max << " start\n";

    for(int i = 1; i <= max; ++i) {
        cout << "\tcoro " << i << "/" << max << "\n";
        co_await std::suspend_always{}; // suspend point
    }

    cout << "\tcoro " << max << " end\n";
}

int main() {
    auto task = coro(5);
    cout << "coro() created\n";

    // loop through coroutine until resume() is true
    while(task.resume()) {
        cout << "coro() suspended\n";
    }
    cout << "coro() done\n";
}

/* Next we will call a coroutine inside an other coroutine */