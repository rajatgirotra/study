/*
 * Variable template can be specialized. Can you try to write compile time variable template which returns the nth fibonacci number?
 * Then try to write an implementation of std::is_same using variable templates
 */

#include <iostream>
#include <cstdint>
#include <iomanip>
#include <type_traits>
#include <cxxabi.h>
#include <string>
#include <cassert>
#include <typeinfo>
using namespace std;

template <int Value> constexpr unsigned long fib = fib<Value-1> + fib<Value-2>;
template <> constexpr unsigned long fib<0> = 0;
template <> constexpr unsigned long fib<1> = 1;

template <typename T, typename U> constexpr bool my_is_same = false;
template <typename T> constexpr bool my_is_same<T, T> = true;

int main() {
    cout << "fib(0): " << fib<0> << endl;
    cout << "fib(1): " << fib<1> << endl;
    cout << "fib(2): " << fib<2> << endl;
    cout << "fib(3): " << fib<3> << endl;
    cout << "fib(4): " << fib<4> << endl;
    cout << "fib(5): " << fib<5> << endl;
    cout << "fib(6): " << fib<6> << endl;
    cout << "fib(7): " << fib<7> << endl;

    cout << "my_is_same<int, int>: " << my_is_same<int, int> << endl;
    cout << "my_is_same<int, volatile int>: " << my_is_same<int, volatile int> << endl;
}

