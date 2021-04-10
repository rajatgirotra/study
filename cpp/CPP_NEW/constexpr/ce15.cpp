/*
 * C++17 allows you to create constexpr lambda functions.
 * Please note that on the resultant function call operator of the closure_type, all rules for regular constexpr function apply like
 *
 * cannot be virtual
 * must return a literal type
 * arguments must all be literal type
 * must not have try-catch block, goto statement, asm blocks
 * cannot have variables which are static or thread local storage or non-literal type
 *
  */

#include <iostream>
#include <type_traits>
using namespace std;

int main() {
    constexpr auto squareValue = [] (int n) { return n*n; };
    static_assert(squareValue(3) == 9);
}