/* Implement fibonacci number generator using a lambda. */

#include <iostream>
#include <functional>
using namespace std;

int main() {
    auto l = [i = 1, j = 0] () mutable {
        // std::exchange first parameter is passed by reference. and the second parameter is a value to set for first parameter.
        // it returns the old value of the first parameter.
        i = std::exchange(j, j+i);
        return i;
    };

    for (auto i = 0; i < 10; ++i)
        cout << l() << "\n";
}