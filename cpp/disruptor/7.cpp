/* Two threads to increment a variable half a billion times.
   using atomic
*/
#include <iostream>
#include <cstdint>
#include <thread>
#include <vector>
#include <atomic>
using namespace std;

namespace {
std::atomic<uint32_t> foo {};
void increment() {
    for (auto i = 0; i < 250000000; ++i) {
         ++foo;
    }
}
}

int main() {
    vector<thread> v;
    v.push_back(std::thread(increment));
    v.push_back(std::thread(increment));
    for (auto& t : v) {
        t.join();
    }
    cout << "foo: " << foo << endl;
    return 0;
}

/*
Sometime took only 4 seconds, and sometimes about 12 seconds. I am not quite sure why, but looks like it depends 
on which core the threads get scheduled.
*/
