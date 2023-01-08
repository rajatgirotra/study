/*
 * you already know that coroutines are stackless.
 * If you have two coroutines coro1() and coro2()
 *
 * auto coro1() {
 *    // Do something --> A
 *    // co_await coro2();
 *    // Do something else
 * }
 *
 * auto coro2() {
 *    // Do something --> B
 * }
 *
 * int main() {
 *     task = coro1();
 *     task.resume(); // this will run "Do something at line A". and then co_await coro2().
 *     task.resume();
 * }
 *
 */

#include <iostream>
#include <string>
#include <coroutine>
#include <exception>
using namespace std;

struct [[nodiscard]] CoroTask {
    struct promise_type;
    using CoroHdl = std::coroutine_handle<promise_type>;

    struct promise_type {
        auto get_return_object() noexcept {
            return CoroTask{CoroTask::CoroHdl::from_promise(*this)};
        }

        auto initial_suspend() const noexcept { return std::suspend_always{}; }
        auto final_suspend() const noexcept { return std::suspend_always{}; }
        void return_void () noexcept { }
        void unhandled_exception() noexcept { std::terminate(); }
        CoroHdl m_innerHandle{};
    };

    //ctor and dtor
    explicit CoroTask(CoroHdl handle) : m_handle(std::move(handle)) {
    }
    ~CoroTask() { reset(); }

    //disable copy
    CoroTask(const CoroTask&) = delete;

    // enable move
    CoroTask(CoroTask&& arg) : m_handle(std::move(arg.m_handle)) {
        arg.m_handle = nullptr;
    }

    CoroTask& operator = (CoroTask&& rhs) noexcept {
        if(this != &rhs) {
            reset();
            this->m_handle = std::move(rhs.m_handle);
            rhs.m_handle = nullptr;
        }
        return *this;
    }

    void setName(string s) {
        m_taskName = std::move(s);
    }

    const string& getName() const noexcept { return m_taskName; }

    bool resume() noexcept {
        if(!m_handle || m_handle.done()) {
            return false;
        }

        CoroHdl deepestHandle = m_handle;
        while(deepestHandle.promise().m_innerHandle && !deepestHandle.promise().m_innerHandle.done()) {
            deepestHandle = deepestHandle.promise().m_innerHandle;
        }
        deepestHandle.resume();
        return !m_handle.done();
    }

    auto await_ready() noexcept { return false; }
    auto await_suspend(CoroHdl awaitHdl) noexcept {
//        cout << m_taskName << ", awaitHdl address: " << std::addressof(awaitHdl) << endl;
        awaitHdl.promise().m_innerHandle = m_handle;
        return true;
    }
    void await_resume() noexcept { }

    void print() const noexcept {
        cout << m_taskName << ", m_handle: " << std::addressof(m_handle) << endl;
    }

private:
    CoroHdl m_handle;
    string m_taskName{};

    void reset() noexcept {
        if(m_handle) {
            m_handle.destroy();
            m_handle = nullptr;
        }
    }
};

CoroTask coro2() {
    cout << "\t\tcoro2() started\n";
    co_await std::suspend_always{};
    cout << "\t\tcoro2() ended\n";
}

CoroTask coro1() {
    cout << "\tcoro1() started\n";
    co_await coro2();
    cout << "\tcoro1() ended\n";
}

int main() {
    cout << "In main - START\n";
    auto task = coro1();
//    task.setName("coro1");
//    task.print();
    while(task.resume()) {
        cout << "coro1() suspended\n";
    }
    cout << "In main - END\n";
}