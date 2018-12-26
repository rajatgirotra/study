/*
 * Write two function overloads of a template function do_stuff(),
 * 1) one which gets called when template parameter is an integral type and
 * 2) one which gets called when template parameter is a class type.
 */

#include <iostream>
#include <type_traits>
using namespace std;

struct X {};

template <typename T, typename std::enable_if_t<std::is_integral_v<T>>* = nullptr>
void do_stuff(const T& t) {
    cout << "do_stuff called for integral template parameter type\n";
}

template <typename T, typename std::enable_if_t<std::is_class_v<T>>* = nullptr>
void do_stuff(const T& t) {
    cout << "do_stuff called for class template parameter type\n";
}


int main() {
    auto x = 10;
    do_stuff<decltype(x)>(10);
    do_stuff(X());
}