/* C++11 restrictions on constexpr
1) Obviously cannot be virtual
2) Return type should be a literal or reference to a literal
3) Parameter should be a literal or reference to a literal
4) Should have a single return statement, cannot do cout, etc

and the most important thing: Unevaluated sub-expressions are ignored. So if there is a throw inside a constexpr, if it is not triggered at compile time, it will be ignored. We'll come to this later.

1) We can still call other constexpr functions
2) We can do compound statement
3) Ternary statements
4) Recursion (ie calling a constexpr function from within-itself)

*/

#include <iostream>
#include <type_traits>
using namespace std;

constexpr int getValue() {
    cout << "Hello" << endl;
    /* cout << is nothing but a call to operator << in ostream, this function is not constexpr, so the compiler complains that you are calling a non-constexpr function inside a constexpr function */
    return 3;
}
int main(int argc, char *argv[]) {
    constexpr int i = getValue();
    cout << i << endl;
    return 0;
}
