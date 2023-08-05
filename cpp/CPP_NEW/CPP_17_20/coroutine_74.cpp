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
#include <syncstream>
using namespace std;

auto syncOut (std::ostream& os= std::cout) {
    return osyncstream(os);
}

struct [[nodiscard]] CoroTask {
    struct promise_type;
    using CoroHdl = std::coroutine_handle<promise_type>;
private:
    CoroHdl m_handle{nullptr};
public:
    explicit CoroTask(auto handle) : m_handle(handle) {}
    ~CoroTask() { reset(); }

    // disable copy and enable move
    CoroTask(const CoroTask&) = delete;

    CoroTask(CoroTask&& rhs) : m_handle(std::move(rhs.m_handle)) {
        rhs.m_handle = nullptr;
    }

    CoroTask& operator = (CoroTask&& rhs) noexcept {
        if(this != &rhs) {
            reset();
            m_handle = std::move(rhs.m_handle);
            rhs.m_handle = nullptr;
        }
        return *this;
    }

    bool resume() {
        if(!m_handle || m_handle.done()) {
            return false;
        }

        // resume should look into the deepest coroutine_handle and resume that.
        CoroHdl deepest_coro = m_handle;
        while(deepest_coro.promise().m_inner_handle && !deepest_coro.promise().m_inner_handle.done()) {
            deepest_coro = deepest_coro.promise().m_inner_handle;
        }
        deepest_coro.resume();
        return !m_handle.done();
    }

    void reset() {
        if(m_handle) {
            m_handle.destroy();
            m_handle = nullptr;
        }
    }

    struct promise_type {
        auto get_return_object() {
            return CoroTask(CoroHdl::from_promise(*this));
        }

        auto initial_suspend() const noexcept { return std::suspend_always{}; }
        auto final_suspend() const noexcept { return std::suspend_always{}; }

        void unhandled_exception() { std::terminate(); }

        void return_void() noexcept {}

        CoroHdl m_inner_handle{};
    };

    bool await_ready() const noexcept { return false; }
    auto await_suspend(CoroHdl await_handle) const noexcept {
        // Note the await_handle is the coroutine_handle<> of the outer coroutine.
        // but the *this object is that of the inner coroutine
        await_handle.promise().m_inner_handle = m_handle;

        // note the subtle difference when this is return enabled. it means no suspension is required and the inner sub coroutine should be
        // resumed straightaway.
        return m_handle;
    }

    void await_resume() const noexcept { }
};

CoroTask coroThree() {
    syncOut() << "\t\tcoroThree started\n";
    co_await  std::suspend_always{};
    syncOut() << "\t\tcoroThree done\n";
}

CoroTask coroTwo() {
    syncOut() << "\t\tcoroTwo started\n";
    co_await coroThree();
    syncOut() << "\t\tcoroTwo done\n";
}

CoroTask coroOne() {
    syncOut() << "\tcoroOne started\n";
    co_await coroTwo();
    syncOut() << "\tcoroOne done\n";
}

int main() {
    auto task = coroOne();
    cout << "coroOne created\n";
    while(task.resume()) {
        cout << "coroOne suspended\n";
    }
    cout << "coroOne finished\n";
}

/* the most important thing to remember is the co_await call.
 * it is called like this:
 * co_await coroTwo() or
 * co_await coroThree()
 * What this does is initialize the coroutine interface objects (CoroTask) for coroTwo and coroThree. and since these coroutine interface objects
 * also implement the Awaitable contract functions (await_*), the co_await call is allowed.
 *
 * So when co_await callTwo() is called, the coroutine awaited is CoroOne, so the await_suspend(await_handle) of coroTwo()'s coroutine interface object
 * is called and await_handle argument is the std::coroutine_interface<> of the coroOne() coroutine.
 */