/*
constexpr is about finding values of things at compile time. So it allows the compiler to evaluate expressions at compile time if possible. constexpr is implicitly const. You cannot change at runtime. 

Good thing is that you can catch errors earlier at compile time. Also your memory footprint is smaller. There is no run time cost.

constexpr implementation differs in C++11 and 14 slightly. We will explore this.

So what things can be constexpr
1) Object. When you define them
2) static data members of a class
3) Functions declarations (including member functions in class)
4) constructors

functions which are declared with constexpr has some constraints in C++11. Some of these constraints are relaxed in C++14.
*/

#include <iostream>
#include <type_traits>
using namespace std;

int main(int argc, char *argv[])
{
    //constexpr int const_3 = 3;  // const_3 is 3 at compile time
    static const int const_3 = 3; // so is here. At this point both static const and constexpr are interchangeable, but you'll see soon what the differences are. Both these can be used in static_assert() confirming they are evaluated at compile time.
    // const_3++; // !error - implicitly const
    static_assert(const_3 == 3, "Value of const_3 should be 3");

    constexpr double half = 0.5;
    //static const double half = 0.5; // with floating points, static const is not evaluated at compile time. So if we use it in static_assert(), we get a compile time error. But with constexpr we can use floating points at compile time.
    cout << "constexpr double = " << half << endl;
    static_assert(half < const_3, "is 0.5 not less than 3");

    constexpr char hello[] = "hello";
    static_assert(hello[5] == '\0', "index 5 should a null!");
    return 0;
}
