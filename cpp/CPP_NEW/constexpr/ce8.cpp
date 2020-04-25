/* C++11 restrictions on constexpr c'tor
1) Cannot have a body.
2) No try-catch block
3) All base c'tor should be constexpr as well
4) All non-static member variables should be initialized in the initializer list
5) Params must be a literal or a refernce to a literal.

C++14 relaxes a lot of this:
in C++14 it says what you cannot do. So you dont do these things, the c'tor body can do everything else.
in fact normal functions can also have more statements not just one like in C++11. so we dont need the recursive implementation we did in ce7.cpp. Lets write a non-recursive function now.
*/

/* constexpr recursive function calls to compute pow(A, B) */

#include <type_traits>
#include <iostream>
using namespace std;

constexpr double ce_pow(double base, int exponent) {
    if ((exponent < -100) || (exponent > 100))
        throw std::runtime_error("abs(exp) > 100");
    if (exponent < 0)
        return ce_pow(1/base, exponent*-1);
    else if (base == 0)
        return 0;
    else if (exponent == 0)
        return 1;
    else if ((exponent%2) == 0)
        return (base*base*ce_pow(base, exponent/2));
    else
        return base * ce_pow(base, exponent-1);
}

int main() {
    constexpr double x = ce_pow(2, -5);
    cout << x << endl;

    //constexpr double y = ce_pow(1, 101);
}
