/*
You have already seen how jthread supports asynchronously stopping a thread using stop_token.
note that jthread establishes all the machinery in its implementation to use stop_token and stop_source.

It even works when the thread is detached.
*/
#include <algorithm> 
#include <unordered_map>
#include <vector>
#include <iterator>
#include <iostream>
#include <thread>
#include <stop_token>
#include <chrono>
using namespace std;
using namespace std::literals;

void detached_task(std::stop_token st) {
    static int log_line = 1;
    while(!st.stop_requested()) {
        cout << "log line " << log_line++ << endl;
        std::this_thread::sleep_for(3ms);
    }

    cout << "stop requested, exiting thread" << endl;
}

int main() {
    std::jthread t{std::ref(detached_task)};

    // detach thread
    t.detach();

    // sleep for 30 ms
    std::this_thread::sleep_for(30ms);

    // request stop
    auto stop_source = t.get_stop_source();
    stop_source.request_stop();

    cout << "main thread will exit in a moment\n";
    std::this_thread::sleep_for(30ms);
}

/*
Just a random note. If you have a threadpool of jthread and you want to join them. always do request_stop first().

for(auto&& t : threads) {
	t.request_stop();
}

for(auto&& t : threads) {
	t.join();
}

request_stop() and join() in one for loop will slow down sending request to stop to all threads.
*/