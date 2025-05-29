#include <iostream>
#include <string>
#include <thread>
#include <future>
#include <chrono>
#include <future>
#include <mutex>
#include <condition_variable>
#include <fstream>
#include <syncstream>
#include <queue>
using namespace std;
using namespace std::literals;

auto syncOut = [](std::ostream& os = std::cout) {
    return std::osyncstream {os};
};

std::mutex mtx;
std::condition_variable_any cv;
std::queue<string> messagesQ;

void consumer(std::stop_token st) {
    // continuously check for messages in queue. if message exists, pop it and print it.
    while(!st.stop_requested()) {
        std::unique_lock<std::mutex> lck(mtx);
        bool res = cv.wait_for(lck, st, 1s, [] { return !messagesQ.empty();});
        if(res) {
            auto msg = messagesQ.front();
            messagesQ.pop();
            syncOut() << "message: " << msg << endl;
        } else {
            if(st.stop_requested()) {
                break;
            } else {
                syncOut() << "no message in queue since 1s.\n";
            }
        }
    }
    syncOut() << "stop requested. exiting consumer thread with " << messagesQ.size() << " messages in queue.\n";
}

auto start_consumer() {
    return std::jthread(std::cref(consumer));
}

void stop_consumer(auto&& arg) {
    arg.request_stop();
}

int main() {
    auto&& t = start_consumer();

    // producer
    string msgs[]{"msg1", "msg2", "msg3", "msg4", "msg5"};
    for(auto&& m : msgs) {
        {
            std::scoped_lock lck(mtx);
            messagesQ.push(m);
        }
        cv.notify_one();
        if(m == "msg5") // don't sleep after last message
            break;
        std::this_thread::sleep_for(3s);
    }

    {
//        std::this_thread::sleep_for(1s);
        std::scoped_lock lck(mtx);
        messagesQ.push("Done");
    }
    cv.notify_one();

    stop_consumer(t);
}