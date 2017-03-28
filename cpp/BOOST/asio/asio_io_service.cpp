#include <boost/asio/io_service.hpp>
#include <iostream>
#include <chrono>
#include <thread>
using std::cout;
using std::endl;

int main() {
    boost::asio::io_service service;
    // cout << service.id << endl;
    service.dispatch([&]() {
            cout << "Hello Asio" << endl;
            service.post([]() {  // --> A
            // service.dispatch([]() {
                    std::this_thread::sleep_for(std::chrono::seconds(10));
                    cout << "Hello Asio second time" << endl;
                });
            cout << "After Post" << endl;
        });

    // service.run();
    service.run_one();
    // service.poll();
    // service.poll_one();
    return 0;
}

/* Subtle difference between post and dispatch
post will never call the handler directly, it will always postpone it by handing over to the io_service
dispatch can call the handler directly, if dispatch is called within a thread which has called run(), run_once(), poll() or poll_once()

If you use post version above in line A, then "After Post" will be called straight-away. It you use
dispatch then "Hello Asio second time will be called before "After Post"

Also notice the difference between run() and run_one() 
run() blocks until there are no more handlers to execute.
run_one() blocks until there is one handler to execute, executes it and returns.
However, if you use the "dispatch()" version above and use run_one(), even in that case
asio runs both the dispatch handlers. Because the second dispatch() calls the function directly without giving it to io_service,
so really its not a handler to be executed for io_service.

Also we have poll() and poll_one() - poll() means do not block, just execute all the ready handlers and return.
poll_one() is also similar but only executes at most one handler.
*/
