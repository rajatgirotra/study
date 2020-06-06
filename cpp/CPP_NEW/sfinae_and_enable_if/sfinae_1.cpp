/*
 * SFINAE means substitution failure is not an error. It is the compiler process of eliding from the overload resolution
 * set, templates where parameter substitution would result in an error.
 */

#include <iostream>
using namespace std;

double negative(double arg) {
    return (-arg);
}

template <typename T>
typename T::result_type negative(T arg) {
    auto t(arg);
    return t.negate();
}

int main() {
    int i = 10;
    auto res = negative(i);
    cout << res << endl;
}

/* since T::result_type for T=int is invalid, the compiler elides it from the overload resolution set.
 */