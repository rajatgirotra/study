#include <iostream>
#include <iomanip>
#include <semaphore>
#include <thread>
#include <chrono>
#include <mutex>
#include <queue>
#include <vector>
#include <syncstream>
#include <coroutine>
#include <memory>
using namespace std;
using namespace std::literals;

struct [[nodiscard]] CoroGen {
    struct promise_type {
    private:
        int m_value{};
    public:
        auto get_return_object() noexcept {
            return CoroGen{CoroGen::CoroHdl::from_promise(*this)};
        }

        auto initial_suspend() noexcept { return std::suspend_always{}; }
        auto final_suspend() noexcept { return std::suspend_always{}; }
        void return_void() noexcept {}
        auto yield_value(int val) noexcept {
            m_value = val;
            return std::suspend_always{};
        }
        void unhandled_exception() noexcept { std::terminate(); };

        int getValue() const noexcept { return m_value; }
    };
    using CoroHdl = std::coroutine_handle<promise_type>;

    explicit CoroGen(CoroHdl handle) : m_handle(std::move(handle)) {}
    ~CoroGen() noexcept { reset(); }

    //disable copy
    CoroGen(const CoroGen&) = delete;

    // enable move
    CoroGen(CoroGen&& arg) : m_handle(std::move(arg.m_handle)) {}
    CoroGen& operator = (CoroGen&& rhs) {
        if(this != &rhs) {
            reset();
            m_handle = std::move(rhs.m_handle);
            rhs.m_handle = nullptr;
        }
        return *this;
    }

    bool resume() noexcept {
        if(!m_handle || m_handle.done()) {
            return false;
        }
        m_handle.resume();
        return !m_handle.done();
    }
    int getValue() const noexcept {
        return m_handle.promise().getValue();
    }

private:
    CoroHdl m_handle;

    void reset() noexcept {
        if(m_handle) {
            m_handle.destroy();
            cout << "CoroGen frame destroyed\n";
        }
    }
};

CoroGen coro() {
    cout << "\tcoro() started\n";
    for(int i = 0; i < 5; ++i) {
        cout << "\t\tcoro() " << i << endl;
        co_yield i;
    }
    cout << "\tcoro() ended\n";
}

int main() {
    auto task = coro();

    cout << "In Main\n";
    while(task.resume()) {
        auto val = task.getValue();
        cout << "\tcoro suspended and yielded: " << val << "\n";
    }
    cout << "Main Ended\n";

}