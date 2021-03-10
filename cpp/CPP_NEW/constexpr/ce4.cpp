/*
constexpr function 
*/

#include <iostream>
#include <type_traits>
using namespace std;

constexpr double half_of(double x) noexcept {
    return x/2;
}

double square(double x) noexcept {
    return x*x;
}

constexpr int twice(int x);
// Both declaration and definition must be constexpr. Also constexpr functions are implicitly inlined. Note that inline only hints the linker
// that there may be multiple definitions of the function in multiple translation units, so sort that out.
// Also constexpr being implicitly inlined means that constexpr member function declared in a header file cannot be defined in the source file. It must be
// defined in the header file itself; as the compiler must see the definition at compile time to be able to compute it at compile time.

int main() {
    // Case 1. parameter x is constexpr, so compiler can evaluate x/2 at compile time.
    constexpr double half_one = half_of(1);  // note this. This is how you tell the compiler that you need constexpr evaluation.
    static_assert(half_one == 0.5, "They should be equal");

    // case 2. parameter d is not constexpr, so compiler will compute  at run time
    double d;
    cin >> d;
    //constexpr double half_again = half_of(d); // ERROR. since d is not constexpr, compiler cannot compute half_of(d) at compile time. So half_again cannot be a constexpr. So we need to take out constexpr from the expression.
    double half_again = half_of(d);
    cout << half_again << endl;

    constexpr double number = 5;
    // constexpr auto answer = square(number); // error again, as this time argument is constexpr, but function is not.

    //static_assert(twice(2)==4, "twice of 2 is not 4!!"); // this fails too!! Why, because the standard says that a constexpr function does not have to be defined before its first use, however the result of any call made prior to its definition is not a constant expression.
    //constexpr auto result = twice(2); 
    int arr2[twice(2)]; // is evaluated at run time; as compiler can't see the definition yet.
    return 0; 
}

// constexpr usage in function declarations does not turn off RVO.
// So there is no function call at all during runtime.
constexpr int twice(int x) {
    return x * 2;
}
