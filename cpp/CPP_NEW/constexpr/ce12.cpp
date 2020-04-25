/* Here we take out the constexpr from 
 auto a = binary<>("1000,0001");
then a is no longer a constexpr. this means we'll have to use an assert instead of static_assert.
And if we give an invalid literal, we will get an exception at Run time.
*/

#include <iostream>
#include <string>
#include <type_traits>
#include <cstdint>
#include <limits>
#include <cassert>
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
    auto a = binary<>("1000,0001");
    assert(a == 129);
    cout << a << endl;
    return 0;
}
