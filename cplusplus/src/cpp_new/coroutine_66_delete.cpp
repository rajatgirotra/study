#include <iostream>
#include <string>
#include <coroutine>
using namespace std;

class [[nodiscard]] CoroTask {
public:
    struct promise_type;
    using CoroHdl = std::coroutine_handle<promise_type>;

    //ctor
    explicit CoroTask(CoroHdl hdl) : m_handle(hdl) {}

    ~CoroTask() {
        if (m_handle) {
            m_handle.destroy();
        }
    }

    CoroTask(const CoroTask&) = delete;
    CoroTask& operator=(const CoroTask&) = delete;
    CoroTask(CoroTask&&) = delete;
    CoroTask& operator=(CoroTask&&) = delete;

    bool resume() {
        if (m_handle && !m_handle.done()) {
            m_handle.resume();
            return !m_handle.done();
        }
        return false;
    }

private:
    CoroHdl m_handle;
};

class CoroTask::promise_type {
public:
    auto get_return_object() {
        return CoroTask(CoroHdl::from_promise(*this));
    }

    auto initial_suspend() noexcept {
        cout << "\tpromise_type::initial_suspend()" << endl;
        return std::suspend_always{};
    }

    void unhandled_exception() {
        cout << "\tpromise_type::unhandled_exception()" << endl;
        std::terminate();
    }

    void return_void() {
        cout << "\tpromise_type::return_void()" << endl;
    }

    auto final_suspend() noexcept {
        cout << "\tpromise_type::final_suspend()" << endl;
        return std::suspend_always{};
    }
};

CoroTask coro(int max) {
    cout << "\tcoro started\n";

    for (int i = 0; i < max; ++i) {
        cout << "\tcoro " << i << "/" << max << "\n";
        co_await std::suspend_always{};
    }
    cout << "\tcoro completed\n";
    co_return;
}

int main() {
    auto task = coro(5);
    cout << "coro initialized\n";
    while (task.resume()) {
        cout << "coro suspended\n";
    }
    cout << "coro done\n";
}