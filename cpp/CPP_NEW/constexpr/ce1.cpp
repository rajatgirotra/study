/*
constexpr is about finding values of things at compile time. So it allows the compiler to evaluate expressions at compile time if possible.
constexpr objects are implicitly const. You cannot change at runtime, as their values are fixed at compile time.

Good thing is that you can catch errors earlier at compile time. Also your memory footprint is smaller. There is no run time cost.

What can be constexpr
 1) objects (static data members of a class can also be constexpr, not regular members)
 2) function (declarations and definitions both, including class member functions, constructors, even setter member functions can be constexpr) as you will see in a bit.

the standard says that if a function is declared constexpr, and all of its arguments are constexpr, then the function must be evaulated at compile time.
 this means to enforce this behavior, there needs to be some restriction on what can be done inside a constexpr function

 in C++11, constexpr functions were really restricted, they could only have a single return statement. But C++14 relaxed this condition
 substantially.

 specifically, putting an I/O operation like cout, or using logger isnt allowed in constexpr.
*/

#include <iostream>

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
    //static_assert(hello[5] == '\0', "index 5 should a null!");
    return 0;
}
