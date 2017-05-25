#include <iostream>
#include <functional>
#include <tuple>
#include <string>
using namespace std;


int main() {
    int a = 10;
    // Obviously an error. You cannot bind an lvalue to a rvalue reference. You need to use std::move
    // tuple<int&&> t1(a);

    tuple<int&&> t1(std::move(a));  // This is OK. Please note that here nothing is moved. std::move() doesnt move anything. It just returns you an rvalue reference. and here the tuple element just references it. So the tuple element and a are the same.
    --a; // element in tuple should now be 9.


    auto x = std::get<0>(t1); // x should be a plain int
    x++; // x is now 10
    a--; // a is 8
    a *=9; // a is 72
    cout << "x: " << x << "  a:" << a << "   in container: " << std::get<0>(t1) << endl; 

    //tuple_element<0, decltype(t1)>::type y = std::get<0>(t1); // error std::get will return you an lvalue reference type and you cannot bind it to an rvalue. Use std::get<0>(std::move(t1)) like below.
    tuple_element<0, decltype(t1)>::type y = std::get<0>(std::move(t1)); // same as explained above. Nothing is getting moved.
    y = y*10; // y should be 720, a should be 720 and so should container
    cout << "y: " << y << "  a:" << a << "   in container: " << std::get<0>(t1) << endl;

    return 0;
}
