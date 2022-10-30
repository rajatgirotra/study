/*
std::counting_semaphore<ptrdiff_t>;

using std::binary_semaphore = counting_semaphore<1>;

Very very trivial. c++20 introduces semaphore as a synchronization primitive. the difference between mutex and semaphore is
that for mutex, the thread acquiring the lock must also be the thread releasing it. But that condition is relaxed with semaphores.

API is also trivial:
counting_semaphore<5> enabled{0}; // create a counting semaphore with max value 5 and current value 0.

acquire() --> atomically try to decrement the semaphore. But if the value is already 0, then block.
release(arg = 1) --> atomically increment the value by arg. Make sure the current value + arg is not greater than the max allowed.
try_acquire()
try_acquire_for()
try_acquire_until()

create an std::queue of a-za-z till 1000 characters. create a counting semaphore of max value 10. initial value 0.
start 10 threads. each thread will wait to acquire the semaphore. if it can, it will pop() the top element
and print it 10 times. then will release the semaphore.

int main() --> only allow 3 threads to run in parallel.
*/

#include <iostream>
#include <iomanip>
#include <vector>
#include <chrono>
#include <thread>
#include <barrier>
#include <cmath>
#include <semaphore>
#include <queue>
#include <mutex>
using namespace std;
using namespace std::literals;

int main() {
    std::queue<char> q;
    std::mutex mtx; // mtx for q
    std::mutex iomtx;
    for(int i = 0; i < 1000; ++i) {
        q.push(static_cast<char>((i % ('z' - 'a')) + 'a'));
    }

    std::vector<std::jthread> threadVec;

    constexpr int numThreads = 10;
    std::counting_semaphore<numThreads> sem{0};

    for(int idx = 0; idx < numThreads; ++idx) {
        threadVec.push_back(std::jthread([idx, &q, &sem, &mtx, &iomtx](std::stop_token st) {
            while(!st.stop_requested()) {
                // try to get semaphore using try_acquire_for. If you use acquire, it will indefinitely block
                // even though a stop is requested.
                if(sem.try_acquire_for(std::chrono::milliseconds(1))) {
                    char ch;
                    {
                        std::lock_guard _(mtx);
                        if(q.empty()) {
                            cout << "Q empty!\n";
                            return;
                        }
                        ch = q.front();
                        q.pop();
                    }

                    // do work
                    {
                        std::lock_guard _(iomtx);
                        cout << idx << ": ";
                        for(int i = 0; i < 10; ++i) {
                            cout << ch;
                        }
                        cout << endl;
                    }
                    std::this_thread::sleep_for(1ms);
  
                    sem.release();
                }
            }
        }));
    }

    sem.release(3);
    std::this_thread::sleep_for(5ms);
    sem.release(2);
    std::this_thread::sleep_for(2ms);
    for(auto&& t : threadVec) {
        t.request_stop();
    }
}