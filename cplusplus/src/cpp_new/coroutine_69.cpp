/* using co_yield to yield a value to coroutine caller */

#include <iostream>
#include <coroutine>
#include <exception>
using namespace std;

// we had CoroTask earlier. Now we create CoroGen as this will yield a value back to caller
struct [[nodiscard]] CoroGen {
    struct promise_type {
        int m_value {};
        auto get_return_object() {
            return CoroGen{CoroGen::CoroHdl::from_promise(*this)};
        }

        auto initial_suspend() noexcept { return std::suspend_always{}; }
        auto final_suspend() noexcept { return std::suspend_always{}; }

        void unhandled_exception() { std::terminate(); }
        void return_void() {}

        auto yield_value(int val) {
            m_value = val;
            return std::suspend_always{};
        }
    };
    using CoroHdl = std::coroutine_handle<promise_type>;
    private:
        CoroHdl m_handle;

    public:
        // ctor and dtor
        explicit CoroGen(auto handle) : m_handle(handle) {}
        ~CoroGen() {
            if(m_handle) {
                m_handle.destroy(); // must always destroy the coroutine frame on memory.
            }
        }    
        
        // disable copy and move to keep things simple
        CoroGen(const CoroGen&) = delete;
        CoroGen(CoroGen&&) = delete;

        bool resume() noexcept {
            // if handle is nullptr of if coroutine has already completed, return false.
            if(!m_handle || m_handle.done()) {
                return false;
            }

            // use the native coroutine API to resume the coroutine.
            m_handle.resume();
            return !m_handle.done();
        }

        auto getValue() {
            return m_handle.promise().m_value;
        }
};

CoroGen coro(int max) {
    cout << "\tcoro() start\n";
    
    for(int value = 1; value <= max; ++value) {
        cout << "\tcoro() " << value << "/" << max << "\n";
        co_yield value;
    }
    
    cout << "\tcoro() end\n";
}

int main() {
    auto task = coro(5);
    cout << "Main: coro() created\n";

    // loop through coroutine until resume() is true
    while(task.resume()) {
        auto value = task.getValue();
        cout << "Main: coro() suspended with value: " << value << "\n";
    }
    cout << "Main: coro() done\n";
}

/*
 next we want to convert our coroutine interface such that we can access the yielded values in a range based for loop
 something like
 for(auto&& val : gen) { // gen is the generator
 }

 instead of using while(task.resume()) loop.
*/