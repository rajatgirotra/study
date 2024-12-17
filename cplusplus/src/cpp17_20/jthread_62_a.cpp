/*
 * Write two threads
 * a producer thread that produces an integer every 1 second and pushes it to a FIFO queue.
 * after a few seconds (say 10 seconds), main thread should request the producer to stop. the thread should notify the consumer thread
 * when a value is pushed to queue.
 *
 * a consumer thread which waits for a value to be available in the queue. It should wait for 0.5 seconds and if no value
 * is available, it should log that. When a value is available, it should print the value and pop it from the queue.
 * this consumer thread should exit if there is no value to consume for 5 seconds.
 *
*/
#include <algorithm> 
#include <unordered_map>
#include <vector>
#include <iterator>
#include <iostream>
#include <thread>
#include <stop_token>
#include <chrono>
#include <condition_variable>
#include <syncstream>
#include <ranges>
#include <queue>
using namespace std;
using namespace std::literals;
namespace rng = std::ranges;
namespace vws = std::views;

auto syncOut(std::ostream& os = std::cout) {
    return osyncstream(os);
}

std::mutex mtx;
std::condition_variable_any cv;
std::queue<size_t> q;

void consumer_function(std::stop_token st) {
    auto unconsumed_tries{0};
    while(true) {
        std::unique_lock<std::mutex> lck(mtx);
        [[maybe_unused]] auto res = cv.wait_for(mtx, st, 0.5s, [] () {
            return !q.empty();
        });
        if(st.stop_requested()) {
            syncOut() << "stop requested, exiting consumer thread with " << q.size() << " unconsumed values\n";
            return;
        } else if (!res) {
//            syncOut() << "no value in queue since 0.5s\n";
            ++unconsumed_tries;
            if(unconsumed_tries == 10) {
                syncOut() << "no value in queue for 5 seconds. exiting consumer thread\n";
                return;
            }
        } else {
            auto value = q.front();
            q.pop();
            syncOut() << "consumed " << value << " from queue\n";
            unconsumed_tries = 0;
        }
    }
}

void producer_function(std::stop_token st) {
    size_t value {1};
    while(!st.stop_requested()) {
        {
            std::lock_guard<std::mutex> lck(mtx);
            q.push(value);
            syncOut() << "pushed " << value << " to queue\n";
        }
        cv.notify_one();
        std::this_thread::sleep_for(1s);
        ++value;
    }
}

int main() {
    std::stop_source ssrc;
    std::jthread producer(std::ref(producer_function), ssrc.get_token());
    std::jthread consumer(std::ref(consumer_function));

    std::this_thread::sleep_for(3s);
    ssrc.request_stop(); // requesting producer to stop.

    // remember we need to wait in main thread. because if the main thread exits.
    // it implicitly calls jthread dtor which calls request_stop() and join() on the consumer thread. So our consumer thread will exit
    // early instead of waiting for 5 seconds.
    std::this_thread::sleep_for(8s);
}