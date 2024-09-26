/*
Another way of handling stop requests is to create callback handler
Whenever a stop is requested, your callback handler is called.
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
        while(!stop_requested.load()) {
            cout << "log line: " << log_line++ << endl;
            std::this_thread::sleep_for(1ms);
        }
    });

    // wait for 1 second and then request cancellation
    std::this_thread::sleep_for(500ms);
    t.request_stop();
}

/*
Think which thread will execute the stop_callback?? it is the thread which is requesting the stop.
in this case, it is the main thread.
*/