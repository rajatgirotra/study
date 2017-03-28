/* Single thread program to increment a variable half a billion times.
   variable is atomic
*/
#include <iostream>
#include <cstdint>
#include <atomic>
#include <thread>
using namespace std;

namespace {
void increment() {
    std::atomic<uint64_t> foo {};
    for (auto i = 0; i < 500000000; ++i) {
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
Took about 4.6 seconds, so much slower than the simple single threaded version
but significantly faster than the lock version
*/
