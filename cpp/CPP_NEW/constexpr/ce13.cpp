/* 
Let say we always want everyone to use 
constexpr auto a = binary("00001111"), so no one should forget to use constexpr. 
If someone forgets anyway, then the compiler will evaluate it at run time, this means that the throw will be evaluated and put in the executable.
To avoid a runtime error and make a link time error, there is a cool technique. Just add an unresolved symbol in throw and we'll get a link time error.

*/

#include <iostream>
#include <string>
#include <type_traits>
#include <cstdint>
#include <limits>
#include <cassert>
using namespace std;

extern const char* some_unresolved_symbol;
template <typename T = uint64_t>
constexpr T binary(const char* literal,
                   std::size_t b = 0, // bit count (ie number of 0's and 1's in the input literal
                   T x = T()) {

    return
        *literal == '\0' ? x :
        (b > std::numeric_limits<T>::digits ? throw std::runtime_error(some_unresolved_symbol) :
         *literal == ',' ? binary (literal+1, b, x) :
         *literal == '0' ? binary (literal+1, b+1, (x*2)+0) :
         *literal == '1' ? binary (literal+1, b+1, (x*2)+1) :
        throw std::runtime_error(some_unresolved_symbol));
}

int main() {
    auto a = binary<>("1000,0001"); // should have used a constexpr, but we forgot.
    assert(a == 129);
    cout << a << endl;
    return 0;
}

