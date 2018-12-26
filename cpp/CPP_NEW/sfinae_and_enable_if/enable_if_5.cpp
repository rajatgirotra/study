/*
 * Write two function overloads of a template function construct(), they should have the same function arguments.
 * 1) one returns bool if template parameter is Integral type
 * 2) one returns double if template parameter is Floating type
 */

#include <iostream>
#include <type_traits>
using namespace std;

template <typename T, typename... Args>
typename std::enable_if<std::is_integral_v<T>, bool>::type
construct(T* t, Args&&... args) {
    cout << "function expects integer and returns boolean\n";
}

template <typename T, typename... Args>
typename std::enable_if<std::is_floating_point_v<T>, double>::type
construct(T* t, Args&&... args) {
    cout << "function expects double and returns double\n";
}

int main() {
}