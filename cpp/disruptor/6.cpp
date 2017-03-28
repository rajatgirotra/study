/* Two threads to increment a variable half a billion times.
   takes a lock and releases it. Since two threads are used, program should be slower than 4.cpp
   due to contention.
*/
#include <iostream>
#include <cstdint>
#include <mutex>
#include <thread>
#include <vector>
using namespace std;

namespace {
std::mutex mtx;
uint64_t foo {};
void increment() {
    for (auto i = 0; i < 250000000; ++i) {
        std::lock_guard<std::mutex> lck(mtx);
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
Took about 62 seconds, shit.... !!
*/
