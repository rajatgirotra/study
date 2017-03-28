#include <iostream>
#include <thread>
#include <future>
using namespace std;

int doAsyncWork() {
    cout << "Doing Work\n";
    return 10;
}

int main(int argc, char *argv[])
{
    //auto fut = std::async(doAsyncWork);
    // fut.get();

    // auto t = std::thread(doAsyncWork);
    // t.join();

    auto fut2 = std::async(std::launch::async, doAsyncWork);
    return 0;
}

/*
Prefer std::async (called task based) to std::thread (thread-based). It is because
1) std::async internally manages creation of thread and also returns you a future to easily retrieve the result of the thread function. With std::thread, this is not straight forward

2) Even if your function throws an exception, std::async returns you that exception. std::thread will just terminate if the exception thrown is not caught.

3) You are offloading thread management to C++ library.

Issues with std::async 

1) Default launch policy is:
----------------------
std::launch::async | std::launch::deferred - meaning run the task either async or when someone calls get() function on the future returned by the async call(). When you call get(), typically your function will be run SYNCHRONOUSLY (ie on the same thread on which get() is called)
This means that with the default launch policy, you are not sure if a thread will be created or not.
So if your function uses TLS (thread local storage), you can never be sure which threads local storage is getting used.

2) With wait based functions with timeouts (like wait_for(), wait_until()) with default launch policy, you would do

void f() {
    std::this_thread::sleep_for(1s);  // 1s is defined as a duration in std::literals
}

auto fut = std::async(f); // can be run in async or sync manner.

while(fut.wait_for(100ms) != std::future_status::ready) {  // 100ms is defined as a duration in std::literals
    // will never return as wait_for(100ms) executes and the function never gets a chance to even start.
    Lets see this thread2.cpp
}
*/
