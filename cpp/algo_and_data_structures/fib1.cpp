#include <iostream>
#include <cstdint>
#include <utility>
#include <type_traits>
using namespace std;

// Worst way of computing fibonacci.
// Time complexity is exponential O(2 to the power n)
// Space complexity is
// with c++11 and constexpr we can compute fib at compile time, so runtime complexity is constant.
constexpr uint64_t fib_recursive(int32_t n) {
    if (n <= 1) 
        return n;
    else
        return fib_recursive(n-1) + fib_recursive(n-2);
}

int main(int argc, char* argv[]) {
    constexpr auto x = fib_recursive(100);
    //auto x = fib_recursive(100);
    cout << "fib_recursive(100): " << x << endl;
    static_assert(x==3736710778780434371, "error"); 
    return 0;
}

