#include <iostream>
#include <string>
#include <condition_variable>
#include <mutex>
#include <future>
#include <thread>
#include <chrono>
#include <atomic>
using namespace std;
using namespace std::literals;

namespace {
    std::mutex mtx;
    std::condition_variable cv;
    std::atomic<bool> event_triggered {false};
}

void producer() {
    for (auto i = 0; i< 4; ++i)
    {
        {
            std::unique_lock<std::mutex> _lock(mtx);
            event_triggered.store(false);
        }
        //cv.notify_one();
        cout << "producer set event_triggered to false and called notify_one().\n";
        std::this_thread::sleep_for(2s);
    }
    {
        std::unique_lock<std::mutex> _lock(mtx);
        event_triggered.store(true);
        //cv.notify_one();
        cout << "producer set event_triggered to true and called notify_one().\n";
    }
}

void consumer() {
    while(true) {
        std::unique_lock<std::mutex> _lock(mtx);
        cv.wait_for(_lock, 1s, []() {
            cout << "checking event_triggered\n";
            return event_triggered.load();
        });
        cout << "Wait over\n";
        if(event_triggered.load()) {
            cout << "event triggered is true after wait in consumer\n";
            break;
        } else {
            cout << "event triggered is false after wait in consumer\n";
            continue;
        }
    }
}

int main(int argc, char* argv[]) {

    auto p = std::thread(producer);
    auto c = std::thread(consumer);

    p.join();
    c.join();

    return 0;
}
