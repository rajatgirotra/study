/*
std::jthread has a new feature where you can request thread cancellation using stop tokens.
So your thread callable can take std::stop_token as a first argument and inside your callable, you
can periodically check if someone has requested for your thread to be cancelled.

There is a one to one relation between a jthread and its stop_token by default. Meaning when you dont pass any stop_token, yourself, the default implementation passes a unique stop_token for every thread. However, it is really trivial to create a single stop_source and pass that stop_source to all the threads as normal arguments.
*/
#include <thread>
#include <string>
#include <iostream>
#include <chrono>
using namespace std;
using namespace std::literals;

int main() {
    std::jthread t([](std::stop_token st) {
        static int log_line = 1;
        while(!st.stop_requested()) {
            cout << "log line: " << log_line++ << endl;
            std::this_thread::sleep_for(1ms);
        }
        cout << "Stop requested.. exiting!!\n";
    });

    // wait for 1 second and then request cancellation
    std::this_thread::sleep_for(500ms);
    t.request_stop();
}