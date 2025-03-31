/*
 * stop_source and stop_tokens. C++20 provides a very generic way of requesting to stop other threads
 * asynchronously; using stop_token, stop_source and stop_callbacks.
 * How does it work.
 * 1) You would create an object of stop_source --> By default when you create a stop_source, a shared stop state
      is created by the constructor on the heap. Since this shared stop state is on the heap, it is independent of
      the lifetime of the associated stop_source, stop_token and stop_callback objects.

      This shared state on the heap is managed automatically and destroyed automatically when the last stop_source, stop_token
      stop_callback object gets destroyed.

   2) Second step is you request a stop_token from the stop_source. i.e.

      stop_source ssrc;
      stop_token st = ssrc.get_token();

   3) You can now cheaply pass stop_ssrc and stop_token around in your code freely. These objects are relatively cheap to copy.
      Somewhere in your code you will use ssrc.request_stop() to request a thread to stop asynchronously.
    
   4) the thread which is requested to stop, can either choose to periodically poll the stop_token if a stop was
    requested. Otherwise, it can choose to create stop_callback objects which will be called when a stop is requested.

    you can also choose to create a stop_source without creating a shared stop state upfront (as that requires resources).
    You can see the stop_source API on cppreference. it is very trivial.

    Few things to remember:
    a) the registered callable (stop_callable) is called immediately in the thread where request_stop() was called.
       request_stop() blocks until all registered callables are called. The order of the calls is not defined.
    
    b) but what if the callable was never registered by the time request_stop() was called?? If the callable is registered after
    request_stop() was called, the callable will be called immediately in the thread registering this callback.

    c) If the thread has already finished (i.e. the callable also has been destroyed), the callback will never be called.
*/

#include <iostream>
#include <string>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <chrono>
#include <queue>
#include <stop_token>
#include <syncstream>
#include <future>

using namespace std;
using namespace std::literals;

auto syncOut(std::ostream& strm = std::cout) {
    return osyncstream {strm};
}

void func(std::stop_token stok, int num) {
    auto id = std::this_thread::get_id();
    syncOut() << "call func(" << num << ")\n";

    // register another callback
    stop_callback cb2 {stok, [num, id] () {
        syncOut() << "- STOP2 requested in func(" << num
         << (id == std::this_thread::get_id() ? ")\n" : ") in main thread\n");
    }};
    std::this_thread::sleep_for(9ms);

    // register one more callback
    stop_callback cb3 {stok, [num, id] () {
        syncOut() << "- STOP3 requested in func(" << num
         << (id == std::this_thread::get_id() ? ")\n" : ") in main thread\n");
    }};
    std::this_thread::sleep_for(2ms);

}

int main() {
    // create a shared state and get the token
    std::stop_source ssrc;
    auto stok = ssrc.get_token();

    // register a callback
    stop_callback cb1 {stok, [] () {
        syncOut() << "- STOP requested in main()\n" << std::flush;
    }};

    auto fut = std::async(std::launch::async, [stok] () {
        for(int i = 1; i < 10; ++i) {
            func(stok, i);
        }
    });

    // after a while, request stop
    std::this_thread::sleep_for(50ms);
    ssrc.request_stop();
}

/*
Understand the output: Very trivial.
*/