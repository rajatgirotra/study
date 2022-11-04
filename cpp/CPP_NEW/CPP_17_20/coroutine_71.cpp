/* using co_return to return a value to coroutine caller
Write a coroutine which takes a range and yields the value of each item in the range and then finally
co_returns the average of the items in the range (in double)
 */

#include <iostream>
#include <coroutine>
#include <exception>
#include <iterator>
#include <cassert>
#include <ranges>
#include <algorithm>
#include <vector>
using namespace std;
namespace rng = std::ranges;
namespace vws = std::views;

template <typename T>
struct ResultTask {
    struct promise_type {
        T m_result;
        auto get_return_object() {
            return ResultTask{ResultTask::CoroHdl::from_promise(*this)};
        }
        auto initial_suspend() noexcept { return std::suspend_always{}; }
        auto final_suspend() noexcept { return std::suspend_always{}; }
        auto return_value(double val) { m_result = val; }
        void unhandled_exception() { std::terminate(); }
    };

    using CoroHdl = std::coroutine_handle<promise_type>;
    private:
        CoroHdl m_handle;

    public:
        ResultTask(auto handle) : m_handle(handle) {}
        ~ResultTask() {
            if(m_handle) {
                m_handle.destroy();
                m_handle = nullptr;
            }
        }

        // disable copy
        ResultTask(const ResultTask&) = delete;

        // enable move
        ResultTask(ResultTask&& rhs) : m_handle(std::move(rhs.m_handle)) {
            rhs.m_handle = nullptr;
        }

        ResultTask& operator = (ResultTask&& rhs) {
            if(this != &rhs) {
                if(m_handle) {
                    m_handle.destroy();
                }
                m_handle = std::move(rhs.m_handle);
                rhs.m_handle = nullptr;
            }
            return *this;
        }

        T getResult() noexcept {
            return m_handle.promise().m_result;
        }

        bool resume() {
            if(!m_handle || m_handle.done()) {
                return false;
            }
            m_handle.resume();
            return !m_handle.done();
        }
};

ResultTask<double> average(auto coll) {
    cout << "\tcoro() begin\n";
    double sum = 0;

    for(auto&& item : coll) {
        sum += item;
        cout << "\tprocess item " << item << endl;
        co_await std::suspend_always{};
    }

    double average = sum / static_cast<double>(std::ssize(coll));
    co_return average;
}

int main() {
    std::vector values {9, 7, 8, 12, 0, -7, 2};
    auto task = average(vws::all(values));
    cout << "MAIN: coro() created\n";

    while(task.resume()) {
        cout << "MAIN: resume()\n";
    }

    cout << "result: " << task.getResult();
}