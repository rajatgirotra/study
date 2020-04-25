/*
What we can do with constexpr is create a binary literal. Ie a constexpr function which takes a string literal of 0's and 1's and returns the corresponding equivalent in decimal at compile time. 
You would done this already in template metaprogramming. So let's do in that first and then think about how to do with constexpr
*/

#include <iostream>
#include <string>
#include <type_traits>
#include <cstdint>
using namespace std;

template <uint64_t N>
struct bin2dec {
    static const uint64_t value = bin2dec<N/10>::value << 1 | N%10;
};

template <>
struct bin2dec<0> {
    static const uint64_t value = 0;
};

int main() {
    cout << bin2dec<0>::value << endl;
    cout << bin2dec<1>::value << endl;
    cout << bin2dec<10>::value << endl;
    cout << bin2dec<11>::value << endl;
    cout << bin2dec<10001>::value << endl;
    return 0;
}
