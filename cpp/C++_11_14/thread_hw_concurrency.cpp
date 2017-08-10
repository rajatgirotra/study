/*
std::thread provides an API:

static unsigned int hardware_concurrency() which returns the number of threads supported on the system. If this value cannot be computed or is not well defined, returns 0
*/

#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <mutex>
#include <sched.h>

using namespace std;
int main() {
    auto num_cpus = std::thread::hardware_concurrency();
    cout << "Number of threads that can run in parallel: " << num_cpus << endl;

    std::vector<std::thread> threadList;
    std::mutex iomutex;
    for (auto i = 0; i < num_cpus; ++i) {
        threadList.emplace_back(std::thread([&iomutex, i] () {
            while(1) {
                {
                    std::lock_guard<std::mutex> lck(iomutex);
                    // sched_getcpu() returns the logical cpu on which this thread is running
                    cout << "Thread #" << i << " running on cpu "<< sched_getcpu() << endl;
                } // iomutex will be released at the end of this scope.
                std::this_thread::sleep_for(std::chrono::seconds(2));
            }
        }));
    }

    for(auto& t: threadList)
        t.join();

    return 0;
}

/*
1) Run as usual ./a.out
2) Then run using taskset, example "taskset -c0,1 ./a.out" to run the program on logical cpus 0 and 1.
3) The same effect can also be obtained using sched_set_affinity() or pthread_affinity_np()
*/
