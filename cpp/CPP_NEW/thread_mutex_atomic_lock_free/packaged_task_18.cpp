/*
 * template <typename T>
 * std::packaged_task; // no definition
 *
 * template <typename ResultType, typename... Args>
 * std::packaged_task<ResultType(Args&&... args)>;
 *
 * basically just a wrapper which wraps a callable and also store the result from that callable.
 * the result can then be accessed via the future object provided by the task.
 *
 * We'll try to wrap a lambda, an std::bind expression and a simple function.
 */

#include <iostream>
#include <future>
#include <thread>
#include <mutex>
#include <string>
#include <chrono>
#include <functional>
using namespace std;
using namespace std::placeholders;

std::mutex iomutex; // used to synchronize I/O

int f(int x, int y) {
    return x * y;
}

int main() {
    // packaged task wrapping a simple function
    std::packaged_task<int(int, int)> task(std::ref(f));
    auto future_1 = task.get_future();
    // run task
    task(3, 4); // runs synchronously. Wrap in std::thread if you want async.
    cout << future_1.get() << endl;


    // packaged task wrapping a lambda
    std::packaged_task<int(int, int)> task_2([] (int x, int y) {
        return 2* x * y;
    });
    auto future_2 = task_2.get_future();
    auto td = std::thread(std::move(task_2), 8, 9);
    td.join();
    cout << future_2.get() << endl;


    // packaged task wrapping an std::bind expression
    std::packaged_task<int(int, int)> task_3(std::bind(std::ref(f), _1, _2));
    auto future_3 = task_3.get_future();
    auto t = std::thread(std::move(task_3), 10, -10);
    t.join();
    cout << future_3.get() << endl;
}