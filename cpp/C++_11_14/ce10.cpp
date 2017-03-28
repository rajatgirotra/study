#include <iostream>
#include <string>
#include <type_traits>
#include <cstdint>
#include <limits>
using namespace std;

template <typename T = uint64_t>
constexpr T binary(const char* literal,
                   std::size_t b = 0, // bit count (ie number of 0's and 1's in the input literal
                   T x = T()) {

    return
        *literal == '\0' ? x :
        (b > std::numeric_limits<T>::digits ? throw std::runtime_error("Too many bits!!") :
         *literal == ',' ? binary (literal+1, b, x) :
         *literal == '0' ? binary (literal+1, b+1, (x*2)+0) :
         *literal == '1' ? binary (literal+1, b+1, (x*2)+1) :
        throw std::runtime_error("Only 0's, 1's and commas are allowed"));
}

int main() {
    constexpr auto a = binary<>("1000,0001");
    static_assert(a == 129, "Gosh!!");
    // constexpr uint64_t b = binary("1000,00012");
    return 0;
}

/* With c++14 this is even easier as we can use a for loop to iterate over the string literal and a switch case to check for ',', '0', or '1'
 */
