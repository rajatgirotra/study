/*
 * SFINAE means substitution failure is not an error. It is the compiler process of eliding from the overload resolution
 * set, templates where parameter substitution would result in an error.
 */

#include <iostream>
using namespace std;

int negative(int t) {
    cout << "non template version\n";
    return t * -1;
}

template <typename T>
typename T::result_type negative(T value) {
    cout << "template version\n";
    T t(value);
    return t.negate();
}

int main() {
    int x = 10;
    cout << negative(x) << endl;
}

/* since T::result_type for T=int is invalid, the compiler elides it from the overload resolution set.
 */