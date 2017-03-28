/* C++11 introdices a new syntax for function declarations.
 * Used in cases where the return type of a function depends on an expression
 * processed with the arguments.
 */

#include <iostream>
#include <limits>
#include <typeinfo>
#include <iomanip>
using namespace std;

template <typename T1, typename T2>
auto add(T1 x, T2 y) -> decltype(x+y)
{
     return (x+y);
}

auto subtract(double d1, double d2) -> decltype(d1-d2)
{
   return (d1-d2);
}

int main()
{
    //auto a = add(numeric_limits<int>::max() - 2, 1);
    //auto a = add(numeric_limits<int>::max() - 2, 2);
    //auto a = add(numeric_limits<int>::max() - 2, 3);
    auto a = add(numeric_limits<int>::max() - 2, 1.);
    cout << "type a = " << typeid(a).name() << endl;
    cout << std::fixed << "a = " << a << endl;
}

/*
 * No type promotions here based on actual values. Because everything is compile time 
 */
