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
construct([[maybe_unused]] T* t, [[maybe_unused]] Args&&... args) {
    cout << "function expects integer and returns boolean\n";
    return true;
}

template <typename T, typename... Args>
typename std::enable_if<std::is_floating_point_v<T>, double>::type
construct([[maybe_unused]] T* t, [[maybe_unused]] Args&&... args) {
    cout << "function expects double and returns double\n";
    return 0.;
}

// Since one of the two functions will get elided by the compiler from the overload resolution set,
// only one function will remain in the overload resolution set.
int main() {
    int i = 10;
    construct(&i, 10, 20, 30);
    double d = 10.0;
    construct(&d, 10, 20, 30);
}