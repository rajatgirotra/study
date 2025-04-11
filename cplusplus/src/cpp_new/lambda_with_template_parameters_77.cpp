/*
Before C++20, the closure class provided NO callable default ctor or assignment. With C++20, that is allowed.

auto cmp1 = [] () {...}

auto cmp2 = cmp1; // Ok with C++11.
decltype(cmp) cmp3; // Error before C++20
cmp1 = cmp2; // Error before C++20

How is it useful. Assume a Consumer class which has a string member. Define a hash map on this Consumer object by defining a hash function
for this class.
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

class Consumer {
private:
    string m_name;

public:
    Consumer(string name) : m_name(name) {}
    Consumer(const Consumer &) = default;
    Consumer(Consumer &&) = default;
    Consumer& operator = (const Consumer &) = default;
    Consumer& operator = (Consumer &&) = default;

    friend ostream& operator << (ostream& os, const Consumer& consumer) {
        os << "Consumer: " << consumer.m_name << endl;
        return os;
    }

    const std::string& name() const { return m_name; }
};

namespace std {
    template<>
    struct hash<Consumer> {
        size_t operator()(const Consumer& consumer) const noexcept {
            return std::hash<string>{}(consumer.name());
        }
    };
}

auto consumerHash = [] (const Consumer& consumer) {
    return std::hash<string>{}(consumer.name());
};


int main() {
    [[maybe_unused]] std::unordered_map<Consumer, int> consumerMap1;
    // OR
    [[maybe_unused]] std::unordered_map<Consumer, int, decltype(consumerHash)> consumerMap2(0, consumerHash);
    //OR
    [[maybe_unused]] std::unordered_map<Consumer, int, decltype(consumerHash)> consumerMap3;
    //Since C++20, lambdas with no captures have a default constructor and an assignment operator:
    //this works because the compiler will use the default no argument ctor to create an object of the closure type.

    // OR, infact you can put the lambda definition right at the moment when constructing the hashMap.
    [[maybe_unused]] std::unordered_map<Consumer, int,
        decltype([] (const Consumer& consumer) {
        return std::hash<string>{}(consumer.name());
    })> consumerMap4; // allowed from C++20 onwards.
}
