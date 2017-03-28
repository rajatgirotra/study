/* Single thread program to increment a variable half a billion times */
#include <iostream>
#include <cstdint>
#include <thread>
using namespace std;

namespace {
void increment() {
    static uint32_t foo {};
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
Took about 1.1-1.2 seconds
*/
