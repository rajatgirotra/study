// Copyright (C) 2015 by RajatGirotra
// tuple in C++11
// read tuple[1234...].cpp and then return here.
/*
Very simple concept. Just a generalization of the concept of pairs.
A tuple is a holder of elements of different types. Similar to C-like strcutues,
but instead of accessing elements by names, in tuple we access by their order.
like 0 for first element, 1 for second element and so on.

Although the concept is pretty simple, but it is not very straight-forward to
understand the API, so we'll take our time and go over each function in detail.
*/

#include <tuple>
#include <iostream>
#include <string>
#include <utility>
#include "45.h"
using std::cout;
using std::endl;
using std::string;
using std::tuple;

/* tuple class is defined like this:
   template <typename... Types>
   class tuple {
   ///;
   };
*/


int main() {
    // Making a tuple.
    // default initialization with 0 for int and 0 for char
    tuple<int, char> t1;

    tuple<int, char> t2(100, 'a');
    // cout << t2 << endl; // operator << is not supported.

    // Can create with any type rvalue reference or using const qualifier.
    auto y = 100;
    // tuple<const int&, double&&> t3(100, 23.25);
    tuple<int&, double&&> t3(y, 23.25);
    auto& x = std::get<0>(t3); // x and y are same.
    x++; // x and y are now 101
    auto& z = std::get<0>(t3);
    z++; // x, y, z are now 102
    cout << x << "  " << y << "  " << z << endl;

    int a[3];
    //tuple<int[]> t4(a);  // this line will error.
    // cannot create with an array type.

    // So to store an array we can make use of std::make_tuple
    auto t5 = std::make_tuple(a);
    // std::make_tuple returns a tuple with each type reduced to its decayed type.
    // For example, a function type is reduced to a pointer to function
    // an array type is reduced to a pointer to array (int*) in the above case
    // const int&, const int, int&& etc are reduced to int.

    cout << "type of std::get<0>(t3) is: " << demangle(typeid(std::tuple_element<0, decltype(t3)>::type).name()) << endl;
    cout << "type of std::get<1>(t3) is: " << demangle(typeid(std::tuple_element<1, decltype(t3)>::type).name()) << endl;
    cout << "type of std::get<0>(t5) is: " << demangle(typeid(std::tuple_element<0, decltype(t5)>::type).name()) << endl;
    return 0;
}
