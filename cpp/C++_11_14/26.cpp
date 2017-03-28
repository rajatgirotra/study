/* 
 * constexpr keyword.
 * Used to force compiler to calculate the value of that expression at compile time.
 * Eg:
 */
#include <iostream>
using namespace std;

//constexpr int square(int x)
int square(int x)
{
    return (x*x);
}

int main()
{
    float a[square(9)];
    return 0;
}
