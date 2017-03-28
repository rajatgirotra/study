/* Using TMP to calculate factorial at compile time */

#include <iostream>
using namespace std;

template <unsigned long Number>
struct Factorial
{
    enum
    {
        RESULT = (Number * Factorial<Number - 1>::RESULT)
    };
};

template <>
struct Factorial<1>
{
    enum
    {
        RESULT = 1
    };
};

int main()
{
    cout << "Factorial of 5 is: " << Factorial<5>::RESULT << endl;
    return 0;
}
