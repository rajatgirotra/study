/*
std::latch: very very trivial. Just an atomic int at its core. multiple threads can decrement the counter.
threads can wait on the latch. they will only unblock when the latch value goes to zero. You cannot reset or increment the counter.

#include <latch>
std::latch latch(10); // initialize with value 10.
latch.count_down(); // to decrement the value
latch.wait(); // to wait on the latch
latch.arrive_and_wait(); // does count_down and wait in one step.
latch.try_wait(); // will return true if latch value is 0, false otherwise. will return immediately.

std::latch and std::barrier are very similar. However, in contrast to latches, when reaching zero an (optional)
callback is called and the std::barrier counter re-initializes to the initial count again.

A barrier is useful when multiple threads repeatedly run perform something together. Whenever all threads have done their task,
the optional callback can process the result or new state and after that the asynchronous computation can continue with the loop

Note that the callback is called by the thread that finally decremented the counter to zero.

create a vector of double of values 1.0 to 8.0.
create 8 threads. each thread will compute the sqrt of each index of the vector. when all done, print the vector in the callback.
Do this 5 times over.
*/

#include <iostream>
#include <iomanip>
#include <vector>
#include <chrono>
#include <thread>
#include <barrier>
#include <cmath>
using namespace std;

int main() {
    std::vector values {1., 2., 3., 4., 5., 6., 7., 8.};

    auto callback = [&values] () {
        for(auto&& val : values) {
            cout << setw(10) << val;
        }
        cout << endl;
    };

    callback(); // print initial values

    std::barrier bar{static_cast<long int>(values.size()), callback};

    std::vector<std::jthread> threadVec;

    for(auto idx = 0UL; idx < values.size(); ++idx) {
        threadVec.push_back(std::jthread ([idx, &values, &bar] () {
            for(int i = 0; i < 5; ++i) {
                values[idx] = sqrt(values[idx]);
                bar.arrive_and_wait();
            }
        }));
    }
}