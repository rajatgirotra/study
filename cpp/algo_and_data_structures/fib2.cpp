#include <iostream>
#include <cstdint>
#include <utility>
#include <type_traits>
using namespace std;

// Iterative version.
// Time complexity is linear O(n)
// Space complexity is
// with c++11 and constexpr we can compute fib at compile time, so runtime complexity is constant.
constexpr uint64_t fib_recursive(int32_t n) {
    if (n <= 1) 
        return n;
    else {
        uint64_t a = 0, b = 1;
        while(--n >= 1) {
            auto x = a+b;
            a = b;
            b = x;
        }
        return b;
    }
}

int main(int argc, char* argv[]) {
    constexpr auto x = fib_recursive(100);
    //auto x = fib_recursive(100);
    cout << "fib_recursive(100): " << x << endl;
    static_assert(x==3736710778780434371, "error"); 
    return 0;
}

