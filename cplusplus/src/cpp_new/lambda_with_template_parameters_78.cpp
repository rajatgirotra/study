/*
In fact C++20 allows lambda's to be passed as template parameters. But not like:
template <typename T> // and T could be a closure class.

Lambdas are allowed to be used as Non type template parameters (i.e. with auto)
template <std::invocable auto GetVat> // std::invocable is a concept that guarantees that GetVat is callable.

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

template <std::invocable auto GetVat>
int addTax(int value) {
    return static_cast<int>(std::round(value * (1 + GetVat())));
}

auto defaultTax = [] {
    return 0.19;
};

int main() {
    cout << addTax<defaultTax>(100);
}