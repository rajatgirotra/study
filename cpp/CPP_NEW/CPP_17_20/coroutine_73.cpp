/* very basic awaiter */

#include <iostream>
#include <coroutine>
#include <string>
#include <exception>
using namespace std;

struct Awaiter {
    bool await_ready() const noexcept { cout << "\t\tawait_ready()\n"; return false; }
    void await_suspend([[maybe_unused]] auto awaitHdl) const noexcept { cout << "\t\tawait_suspend()\n"; }
    void await_resume() const noexcept { cout << "\t\tawait_resume()\n"; }
};

struct CoroTask {
    struct promise_type {
        auto get_return_object() { return CoroTask{CoroTask::CoroHdl::from_promise(*this)}; }
        auto initial_suspend() const noexcept { return std::suspend_always{}; }
        auto final_suspend() const noexcept { return std::suspend_always{}; }
        void return_void() {}
        void unhandled_exception() { std::terminate(); }
    };

    using CoroHdl = std::coroutine_handle<promise_type>;
private:
    CoroHdl m_handle;
public:
    CoroTask(auto handle) : m_handle(handle) {}
    ~CoroTask() {
        if(m_handle) {
            m_handle.destroy();
            m_handle = nullptr;
        }
    }

    CoroTask(const CoroTask&) = delete;

    CoroTask(CoroTask&& rhs) : m_handle(std::move(rhs.m_handle)) {
        rhs.m_handle = nullptr;
    }

    CoroTask& operator = (CoroTask&& rhs) {
        if(this != &rhs) {
            if(m_handle) {
                m_handle.destroy();
            }
            m_handle = std::move(rhs.m_handle);
            rhs.m_handle = nullptr;
        }
        return *this;
    }

    bool resume() const noexcept {
        if(!m_handle || m_handle.done()) {
            return false;
        }
        m_handle.resume();
        return !m_handle.done();
    }
};

CoroTask coro(int max) {
    cout << "\tcoro start\n";
    for(int value = 1; value <= max; ++value) {
        cout << "\tcoro " << value << "\n";
        co_await Awaiter{}; // Note that a new Awaiter object is created everytime co_await is called and destructed after await_resume() is called.
    }
    cout << "\tcoro end\n";
}

int main() {
    auto task = coro(5);
    cout << "MAIN: coro created\n";

    cout << "MAIN: loop\n";
    while(task.resume()) {
        cout << "Main: suspended\n";
    }
    cout << "MAIN: done\n";
}