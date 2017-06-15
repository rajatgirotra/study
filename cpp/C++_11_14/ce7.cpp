/* constexpr recursive function calls to compute pow(A, B) */

#include <type_traits>
#include <iostream>
using namespace std;

constexpr double ce_pow_detail(double base, int exponent) {
    return (base == 0 ? 0 : (exponent == 0 ? 1 : (exponent%2 == 0) ? ce_pow_detail(base*base, exponent/2) :
                                 ce_pow_detail(base*base, exponent/2) * base));
}

constexpr double ce_pow(double base, int exponent) {
    return ((exponent < -100) || (exponent > 100) ?
            throw std::runtime_error("abs(exponent) exceeds 100") :
            exponent >= 0 ? ce_pow_detail(base, exponent) : ce_pow_detail(1/base, exponent*-1));
}

int main() {
    constexpr double x = ce_pow(2, -5);
    cout << x << endl;

    //constexpr double y = ce_pow(1, 101); // exponent is > 100, so ce_pow should error at compile time
}
              
/* Note the throw: Because the throw is not evaluated, it is ignored
   If it is evaluated, throw will cause a compiler error.
ce7.cpp:14:65: error: expression ‘<throw-expression>’ is not a constant-expression
             throw std::runtime_error("abs(exponent) exceeds 100") :
 */
