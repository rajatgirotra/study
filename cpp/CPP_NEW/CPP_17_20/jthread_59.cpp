/*
contrast this with jthread_58.cpp. We deliberately exit the thread even before main thread
requests for cancellation. Note that in this case, the stop_callback doesn't get called as thread
has terminated already. jthread automatically handles this by de-registering the callback handler
when it goes out of scope.
*/
#include <thread>
#include <string>
#include <iostream>
#include <chrono>
#include <atomic>
using namespace std;
using namespace std::literals;

int main() {
    std::jthread t([](std::stop_token st) {
        // to create a callback for stop requests, you need to create a stop_callback object
        // which takes a stop_token and a callable.
        std::atomic_bool stop_requested {false};

        std::stop_callback cb{st, [&stop_requested]() {
            cout << "Stop requested.. exiting\n";
            stop_requested.store(true);
        }};

        static int log_line = 1;
        // while(!stop_requested.load()) {
        while(!stop_requested.load() && log_line < 100) {
            cout << "log line: " << log_line++ << endl;
            std::this_thread::sleep_for(1ms);
        }

        if(log_line >= 100) {
            cout << "thread done. exiting\n";
        }
    });

    // wait for 1 second and then request cancellation
    std::this_thread::sleep_for(500ms);
    cout << "Requesting thread stop\n";
    t.request_stop();
}

/*
Think which thread will execute the stop_callback?? it is the thread which is requesting the stop.
in this case, it is the main thread.
So remember, the registered callable is called immediately in the thread where request_stop() was called.
request_stop() blocks until all registered callables are called. The order of the calls is not defined.
*/