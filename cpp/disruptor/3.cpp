/* Single thread program to increment a variable half a billion times.
   variable is volatile
*/
#include <iostream>
#include <cstdint>
#include <thread>
using namespace std;

namespace {
void increment() {
    static volatile uint32_t foo {};
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
Took about 1.2-1.3 seconds, slightly slower than 2.cpp
*/
