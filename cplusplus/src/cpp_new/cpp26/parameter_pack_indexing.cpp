/*
 *  cpp26 now allows you to index into a parameter pack directly using the index operator [].
 *  previously you had to write some overloads for that.
 *
 *  write a function which takes a parameter pack and an integral index.
 *  it should print the type and the value at that index. try both cpp26 and prior way.
 */

#include <print>
#include <typeinfo>
#include <utility>
#include <cxxabi.h>
#include <string>
using namespace std;

namespace {
    auto demangle(const char* mangled_name) {
        int res {-1};
        auto s = abi::__cxa_demangle(mangled_name, nullptr, nullptr, &res);
        string sres (mangled_name);
        if (res == 0) {
            sres = s;
            free(s);
        }
        return sres;
    }
}

template <typename T>
void print_type_and_value(T&& t) {
    std::println("type: {}, value: {}", demangle(typeid(T).name()), std::forward<T>(t));
}

// cpp26 paramter pack indexing
template <auto Index, typename... Args>
void func26(Args&&... args) {
    print_type_and_value(args...[Index]); // simple
}

template <auto Index, typename Arg, typename... Args>
void func(Arg&& arg, Args&&...) requires (Index == 0) {
    print_type_and_value(std::forward<Arg>(arg));
}

// cpp23 and before
template <auto Index, typename Arg, typename... Args>
void func(Arg&&, Args&&... args) requires (Index > 0) {
    func<Index-1>(std::forward<Args>(args)...);
}

int main() {
    func26<0>(10, 55.5, "Hello World", false);
    func26<1>(10, 55.5, "Hello World", false);
    func26<2>(10, 55.5, "Hello World", false);
    func26<3>(10, 55.5, "Hello World", false);

    func<0>(10, 55.5, "Hello World", false);
    func<1>(10, 55.5, "Hello World", false);
    func<2>(10, 55.5, "Hello World", false);
    func<3>(10, 55.5, "Hello World", false);

}