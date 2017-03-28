// Copyright (C) 2015 by RajatGirotra

// about tuple_size and tuple_element
#include <iostream>
#include <string>
#include <tuple>
#include <utility>
#include <typeinfo>
#include "./43.h"
using std::cout;
using std::endl;
using std::tuple;
using std::tuple_size;
using std::tuple_element;

int main() {
    // tuple_size returns the size. Fairly trivial
    int a[] {1, 2, 3};
    auto t = std::make_tuple(100, a);
    cout << tuple_size<decltype(t)>::value << endl;

    // tuple_element is used to get the type of each variable stored
    // in the tuple
    // tuple<const int&, double&&> t2(100, 23.24);  // ---> Line A
    auto t2 = std::make_tuple(100, 23.24);  // ---> Line B
    tuple_element<0, decltype(t2)>::type int_type = std::get<0>(t2);

    /* With Line A, the following line wont compile, because the type stored
       in tuple is double&& and the type returned by std::get<> is either:
      1) lvalue reference if the tuple object itself is an lvalue
      2) rvalue reference if the tuple object itself is an rvalue
      So since tuple has a name t2 in our case, it returns an lvalue
      which cannot to assigned to an rvalue reference.

      Disable Line A and enable Line B, this time, make_tuple will decay 
      type of second variable to double, so get<> will work as expected.
    */
    tuple_element<1, decltype(t2)>::type double_type = std::get<1>(t2);
    // The following will compile with Line A.
    // std::remove_reference<tuple_element<1, decltype(t2)>::type>::type double_type = std::get<1>(t2);
    cout << "Tuple first element type: "
         << demangle(typeid(int_type).name()) << endl;
    cout << "Tuple second element type: "
         << demangle(typeid(double_type).name()) << endl;
    return 0;
}


/*
I dont need to discuss std::get<> now. Very trivial now.
Returns lvalue or rvalue references to variables based on whether tuple itself
is lvalue or rvalue.
Still 47.cpp shows it more clearly.
*/
