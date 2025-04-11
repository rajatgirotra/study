/*
lambdas can be suffixed with consteval keyword. What this means is that the lambda function must be evaluated at compile time.
If your lambda function takes any arguments, those must be known at compile time obviously, otherwise you can't evaluate the lambda
at compile time. this means that the arguments should be constexpr.
*/

#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <type_traits>
#include <concepts>
#include <random>
#include <ranges>
#include <cxxabi.h>
#include <unordered_map>
#include <variant>
using namespace std;
namespace rng = std::ranges;
namespace vws = std::views;

string demangle(const char *mangled_name) {
    int _{};
    auto demangled_name = abi::__cxa_demangle(mangled_name, nullptr, nullptr, &_);
    string result(demangled_name);
    free(demangled_name);
    return result;
}

auto hashed = [] (const char* str) consteval {
    // any operation here should also be constexpr.
    return sizeof(str);
};

int main() {
    cout << hashed("wine") << endl;

    // const char* s = "beer"; // Error s is not constexpr
    // cout << hashed(s) << endl;

    constexpr const char* s1 = "beer"; // Error s is not constexpr
    cout << hashed(s1) << endl;


    // this lambda is constexpr. a constexpr lambda can be evaluated at compile time if it is used in a context that
    // requires constant evaluation, and all its arguments and operations support compile time evaluation.
    auto isPrime = [](int value) constexpr {
        for (int i = 2; i <= value/2; ++i) {
            if (value % i == 0) {
                return false;
            }
        }
        return value > 1;  // 0 and 1 are no prime numbers
    };

    // local compile-time computation of Num prime numbers:
    // a consteval lambda on the other hand must be evaluated at compile time. It also can only use operations that support
    // compile time evaluation.
    auto primeNumbers = [isPrime] <int Num> () consteval {
        std::array<int, Num> primes;
        int idx = 0;
        for (int val = 1; idx < Num; ++val) {
            if (isPrime(val)) {
                primes[idx++] = val;
            }
        }
        return primes;
    };

    // init array with prime numbers:
    auto primes = primeNumbers.operator()<100>();

    for (auto v : primes) {
        std::cout << v << '\n';
    }
}