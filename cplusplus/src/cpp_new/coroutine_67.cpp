/* coroutine calling another coroutine */

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

CoroTask coro() {
    cout << "\t\tcoro() part 1\n";
    co_await std::suspend_always{}; // suspend point
    cout << "\t\tcoro() part 2\n";
}

CoroTask callCoro() {
    cout << "\tcallcoro() calling sub-coroutine coro()\n";
    coro(); // callin another coroutine
    cout << "\tcallcoro() sub-coroutine coro() done\n";
    co_await std::suspend_always{}; // suspend point
    cout << "\tcallcoro() done\n";
}


int main() {
    auto task = callCoro();
    cout << "Main: callCoro() created\n";

    // loop through coroutine until resume() is true
    while(task.resume()) {
        cout << "Main: callCoro() suspended\n";
    }
    cout << "Main: callCoro() done\n";
}

/*
two things to note. 
First the compilation throws a warning about discarding return value from calling coro()
Second, the cout statements in coro() are not run. that's because the coro() sub-coroutine is
never resumed.

Let's fix both these things next
*/