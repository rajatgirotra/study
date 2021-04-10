/*
 * use fold over comma and create a function which takes a callable and variadic template argument and calls that Callable for every argument.
 */
#include <type_traits>
#include <iostream>
#include <functional>
#include <string>
#include <cxxabi.h>
#include <typeinfo>
using namespace std;

string demangled_name(const char* mangled_name) {
    int result {0};
    auto* demangled_string = abi::__cxa_demangle(mangled_name, nullptr, nullptr, &result);
    string return_string(demangled_string);
    free(demangled_string);
    return return_string;
}

template <typename T>
void MyCallable(T&&) {
    cout << "Callable called with argument of type: " << demangled_name(typeid(T).name()) << endl;
}

auto my_callable = [] (auto&& t) {
    MyCallable(t);
};

template <typename Callable, typename... Args>
void IterArgs(Callable&& callable, Args&&... args) {
    (..., callable(std::forward<Args>(args)));
}

struct A{};

A getA() {return A();}

int main() {
    IterArgs(std::cref(my_callable), string("Hello"), 2., 1, 'x', false, getA());
}

/*
 * remember, fold over comma is very important.
 */