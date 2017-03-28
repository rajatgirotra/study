/* New keyword noexcept, rather called as noexcept operator. Usd with functions to specify that they can't throw.
 * the operator takes a bool (by default, it is true). This boolean can be a condition under which this function will not throw.
 * If the condition is violated, then the functions may throw.
 *
 * Existing problems:
 *
 * 1) The exception specification is always used at runtime. this means that if the exception specification states exception A and your function
 * throws exception B, then it will only be caught at run time and not compile time. So there is also performance overhead.
 *
 * 2) With generic code, you can never be sure what exceptions might be thrown by the different specialisations of your template.
 *
 * 3) Also, unexpected is called if some other exception is thrown which does not allow for recovery.
 *
 * So C++11 has deprecated the use of exception specifications.
 * So now a function can either throw any exception or not throw an exception.
 *
 * If a function with noexcept still throws terminate is called which calls abort.
 */
#include <iostream>
#include <cstdint>
using namespace std;

int foo() noexcept
{
    //throw 'a';
    return 10;
}

int main()
{
    cout << foo() << endl;
    return 0;
}
