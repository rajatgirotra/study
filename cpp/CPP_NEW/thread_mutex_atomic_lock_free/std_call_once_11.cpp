/*
 * std::call_once provides a way where only one of the many threads can run a Callable. Once one thread runs a Callable,
 * all other reads trying to run the same Callable will block. If the original thread is able to run the callable properly,
 * all all threads will be a no-op. If the Callable throws an exception, one of the waiting threads will get a chance to
 * run the callable.
 *
 * Note that for now std::call_once is broken on unix due to issue with pthread_once when the init function throws an exception.
 * The issue needs a fix in glibc. So this code will hang for now.ok
 *
 */
#include <iostream>
#include <string>
#include <future>
#include <mutex>
#include <chrono>
#include <vector>
using namespace std;
using namespace std::literals;

std::mutex m_mtx; // for cout synchronization

std::once_flag ONCE_FLAG;
void foo_can_throw(bool do_throw) {
    std::lock_guard<std::mutex> lg(m_mtx);
    cout << "in function foo_can_throw. " << (do_throw ? "WILL ": "WILL NOT ") << "throw exception\n";
    std::this_thread::sleep_for(1s);
    if (do_throw) {
        throw std::runtime_error("exception from foo_can_throw");
    }
}

void thread_function(bool do_throw) {
    try {
        cout << "Calling call_once\n";
        std::call_once(ONCE_FLAG, std::cref(foo_can_throw), do_throw);
    } catch(const exception& e) {
        std::lock_guard<std::mutex> lg(m_mtx);
        cout << "caught: " << e.what() << endl;
    }
}

int main() {
    using VectorOfThreads = vector<thread>;
    VectorOfThreads vt;
    for(VectorOfThreads::size_type i = 0; i < 4; ++i) {
        vt.emplace_back(std::ref(thread_function), true);
    }

    for(auto&& t : vt) {
        t.join();
        std::lock_guard<std::mutex> _lg(m_mtx);
        cout << "Joined thread\n";
    }

    auto another_thread = std::thread(std::ref(thread_function), false);
    another_thread.join();
}
