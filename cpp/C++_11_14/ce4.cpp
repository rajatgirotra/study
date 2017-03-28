/*
constexpr function 
*/

#include <iostream>
#include <type_traits>
using namespace std;

constexpr double half_of(double x) {
    return x/2;
}

constexpr int twice(int x); // Both declaration and definition must be constexpr. Also constexpr functions are implicitly inlined. So compiler must see the definition in the same transalation unit as it is getting used. 

int main() {
    // Case 1. parameter x is constexpr, so compiler can evaluate x/2 at compile time.
    constexpr double half_one = half_of(1);  // note this. This is how you tell the compiler that you need constexpr evaluation.
    static_assert(half_one == 0.5, "They should be equal");

    // case 2. parameter d is not constexpr, so compiler will compute  at run time
    double d;
    cin >> d;
    cout << half_of(d) << endl;

    int arr2[twice(2)];
    return 0;
}

// constexpr usage in function declarations does not turn off NVRO. Because there is no NVRO. its all at compile time.
// So there is no function call at all during runtime.

constexpr int twice(int x) {
    return x* 2;
}
