//
/*
a simple thread pool using c++20
1. should be able to set affinity of each worker in the thread pool.
   need to have some policies around setting affinity like:
   a. parallel: choose core 0, 1, 2, 3,... for each new worker.
   b. strand: choose the same random cpu.
   c. numa: all workers will be run on the same numa node (default numa will be the numa on which the inherited thread was running)
   d. inherited (also the default): all workers will be scheduled on the
   e. custom: csv list of logical cpus.

2. Ability to allow timeouts on submitted tasks

3. Ability to cancel (cooperative cancellation) a task if it takes too long.

4. Use lock free data structures (maybe from open source) for holding tasks on work queue.

5. Records metrics (like tasks submitted, completed, etc)

6. Per thread tasks counters or monitoring hooks.

7. Graceful shutdown queue draining.

8. Support Work stealing.

9. 100% testable.

Refer this chat.
https://chatgpt.com/share/67fbcbb9-764c-8000-8bab-a05a029b2672
*/

#include <memory>
#include <thread>
#include <future>
#include <mutex>
#include <condition_variable>
#include <tuple>
#include <functional>
#include <algorithm>
#include <ranges>
#include <concepts>
#include <queue>
#include <vector>
#include <iostream>
using namespace std;

namespace rng = std::ranges;
namespace vws = std::ranges::views;

class ThreadPool {
private:
    size_t m_thread_count{1};
    std::mutex m_mutex;
    std::condition_variable_any m_cv;
    std::vector<std::jthread> m_workers;
    std::queue<std::unique_ptr<std::packaged_task<void()> > > m_tasks;

public:
    explicit ThreadPool(size_t thread_count) : m_thread_count(thread_count) {
        for (auto i: vws::iota(0UL, m_thread_count)) {
            m_workers.emplace_back([i=i, this](std::stop_token st) {
                std::unique_ptr<std::packaged_task<void()> > task{};
                while (!st.stop_requested()) {
                    std::unique_lock<std::mutex> lck(m_mutex);
                    m_cv.wait(lck, st, [this]() { return !m_tasks.empty(); });
                    if (st.stop_requested()) { break; }

                    task = std::move(m_tasks.front());
                    m_tasks.pop();
                    try {
                        (*task)();
                    } catch (std::exception &e) {
                        cerr << "Caught exception in worker thread: " << e.what() << endl;
                    } catch (...) {
                        cerr << "Caught unknown exception in worker thread." << endl;
                    }
                }
            });
        }
    }

    ~ThreadPool() {
        for (auto &&worker: m_workers) {
            worker.request_stop();
        }
        m_cv.notify_all();
    }

    template<std::invocable F, typename... Args>
    auto submit(F &&f, Args &&... args) -> std::future<std::invoke_result_t<F, Args...> > {
        // Add callable to queue. since queue contains std::packaged_task<void()>, we need to wrap the invocable and args inside a no argument lambda.
        using return_type = std::invoke_result_t<F, Args...>;

        auto bound_task = [fwd_f = std::forward<F>(f), ...args = std::forward<Args>(args)]() mutable {
            return std::invoke(std::move(fwd_f, std::move(args)...));
        };
        auto task_wrapper = std::packaged_task<return_type()>(std::move(bound_task));
        auto future = task_wrapper.get_future();
        {
            std::unique_lock<std::mutex> lck(m_mutex);
            m_tasks.emplace([task = std::move(task_wrapper)]() mutable {
                (*task)();
            });
        }
        m_cv.notify_one();
        return future;
    }
};

int main() {
    ThreadPool tp{5};
}
