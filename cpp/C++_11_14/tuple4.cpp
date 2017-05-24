#include <iostream>
#include <functional>
#include <tuple>
#include <string>
using namespace std;


int main() {
    int a = 10;
    // Obviously an error. You cannot bind an lvalue to a rvalue reference. You need to use std::move
    // tuple<int&&> t1(a);

    tuple<int&&> t1(std::move(a));  // This is OK.
    cout << a << endl; // Dont assume that a is 10, even if your compiler shows its 10. "a" is now not reliable.


    auto x = std::get<0>(t1); // x should be a plain int
    x++; // x is now 11
    a--;  // a is unreliable, dont use it.
    a *=9;
    cout << "x: " << x << "  a:" << a << "   in container: " << std::get<0>(t1) << endl; 

    tuple_element<0, decltype(t1)>::type y = std::get<0>(t1);
    y = y*10; // y, a, and container all are same.
    cout << "y: " << y << "  a:" << a << "   in container: " << std::get<0>(t1) << endl;

    return 0;
}
