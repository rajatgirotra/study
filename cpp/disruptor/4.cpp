/* Single thread program to increment a variable half a billion times.
   takes a lock and releases it.
*/
#include <iostream>
#include <cstdint>
#include <mutex>
#include <thread>
using namespace std;

namespace {
void increment() {
    static uint32_t foo {};
    std::mutex mtx;
    for (auto i = 0; i < 500000000; ++i) {
        std::lock_guard<std::mutex> lck(mtx);
        ++foo;
    }
    cout << "foo: " << foo << endl;
}
}

int main() {
    std::thread t(increment);
    t.join();
    return 0;
}

/*
Took about 17-18 seconds, so much slower.
*/
