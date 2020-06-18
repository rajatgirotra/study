/*
 * std::thread provides hardware_concurrency() which returns the number of concurrent threads that can be run (basically the number of logical cpus)
 */

#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <chrono>
#include <sched.h>
#include <vector>
using namespace std;

int main() {
    auto num_cpus = std::thread::hardware_concurrency();

    vector<thread> vt;
    std::mutex iomutex;
    for (unsigned int i = 0; i < num_cpus; ++i) {
        vt.emplace_back(std::thread([&iomutex, i] {
            while(1) {
                {
                    std::lock_guard<std::mutex> lg(iomutex);
                    cout << "Thread " << i << " running on cpu: " << sched_getcpu() << endl;
                }
                std::this_thread::sleep_for(1s);
            }
        }));
    }

    for(auto&& t : vt) {
        t.join();
    }
}