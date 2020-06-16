/*
 * If std::async() is called with launch policy std::launch::async, it is run immediately in a separate thread.
 *
 * If std::async() is called with launch policy std::launch::deferred, it is not run immediately. Its run only when you
 * request the return value using the get() or wait() function on the future object returned by std::async. Also its run
 * in the thread which calls get() or wait(), which may be different to the thread which called std::async.
 *
 * If std::async() is called with launch policy std::launch::async|deferred, the running of the thread is implementation
 * defined.
 */

#include <thread>
#include <chrono>
#include <iostream>
#include <functional>
#include <future>

using namespace std;
using namespace std::literals;
int main() {
    cout << "main function running in thread: " << std::this_thread::get_id() << endl;
    // call async with async launch policy
    auto result = std::async(std::launch::async, [] {
        cout << "async function called with async launch policy. thread id: " << std::this_thread::get_id() << ". waiting for one second..\n";
        std::this_thread::sleep_for(1s);
        return 99;
    });
    std::this_thread::sleep_for(3s);
    cout << "async function returned: " << result.get() << endl;

    auto result_2 = std::async(std::launch::deferred, [] {
        cout << "async function called with deferred launch policy. thread id: " << std::this_thread::get_id() << ". waiting for 2 seconds..\n";
        std::this_thread::sleep_for(2s);
        return -178;
    });

    auto&& t = std::thread([&result_2] {
        cout << "fetching result of async with deferred on separate thread with id: " << std::this_thread::get_id() << endl;
        auto res = result_2.get();
        cout << "async with deferred returned: " << res << endl;
    });

    t.join();
}