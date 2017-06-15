#include <iostream>
#include <cstdint>
#include <utility>
#include <type_traits>
#include <boost/optional.hpp>
using namespace std;

boost::optional<uint64_t> fib_store[1000];
// Recurive fibonacci with memoization (top-down dynamic programming approach)
// Time complexity is 
// Space complexity is
uint64_t fib_recursive_memoize(int32_t n) {
    if (fib_store[n]) {
        return *fib_store[n];
    } else {
        fib_store[n] = fib_recursive_memoize(n-1) + fib_recursive_memoize(n-2);
        return *fib_store[n];
    }
}

int main(int argc, char* argv[]) {
    fib_store[0] = 0;
    fib_store[1] = 1;
    auto x = fib_recursive_memoize(100);
    cout << "fib_recursive_memoize(100): " << x << endl;
    return 0;
}

