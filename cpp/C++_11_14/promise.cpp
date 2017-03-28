#include <iostream>
#include <future>
#include <chrono>
#include <thread>
#include <mutex>
#include <condition_variable>
using std::cout;
using std::endl;

// promise is much simple than packaged task
// you dont have to specify any function to a promise
// you just specify the return type of the promis object as a template parameter.
// You can then either use promise::set_value() or promise::set_exception() to set the
// shared state of the promise. Like packaged task, you can retrieve this shared state using
// future.

int wait_for_promise(std::future<int>& fut) {
    auto i = fut.get();
    cout << "Future got "<< i << endl;
}

int main() {
    std::promise<int> prom;
    std::future<int> fut = prom.get_future();

    std::thread th(wait_for_promise, std::ref(fut));

    // full fill promise
    prom.set_value(10);

    th.join();

    return 0;
}
