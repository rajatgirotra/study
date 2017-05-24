// Copyright (C) 2015 by RajatGirotra
// tuple in C++11
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

struct A {
    // A() = delete;
};

template <typename... UTypes>
//void unpack(UTypes&&... t) {
void unpack(tuple<UTypes&...> t) {
//void unpack(tuple<string, int> t) {
    cout << std::get<0>(t) << "   " << std::get<1>(t) << endl;
    cout << "type of std::get<0>(t) is: " << demangle(typeid(typename std::tuple_element<0, decltype(t)>::type).name()) << endl;
    cout << "type of std::get<1>(t) is: " << demangle(typeid(typename std::tuple_element<1, decltype(t)>::type).name()) << endl;
}

int main() {
    tuple<int, char> first;  // will be default initialzed
    tuple<int, char> second(first);  // using copy c'tor
    tuple<int, char> third = std::make_tuple(100, 'a');
    cout << "tuple third: " << std::get<0>(third) << "  "
         << std::get<1>(third) << endl;
    // tuple get<> returns lvalue or rvalue based on what it was
    // created with. In the next exercise, we'll see an example.

    // trying to access 'first' which was default contructed.
    cout << "tuple first: " << std::get<0>(first) << "  "
         << (int)std::get<1>(first) << endl;

    tuple<A> aTuple;  // wont work as default c'tor for A is deleted.

    // tuple from std::pair
    tuple<double, bool> tupleFromPair(std::make_pair(123.12, true));
    cout << "tuple tupleFromPair: " << std::get<0>(tupleFromPair) << "  "
         << std::boolalpha << std::get<1>(tupleFromPair) << endl;

    // tuple_size
    cout << "third tuple size: " << std::tuple_size<decltype(third)>::value
         << endl;
    // tuple_element, again a very simple class that retuns the type of
    // element of the tuple
    std::tuple_element<1, decltype(third)>::type ch = std::get<1>(third);
    cout << "Second Tuple element from third : " << ch << endl;

    // forward_as_tuple, exactly similar to std::forward.
    // Will forward as rvalue or lvalue based on what you pass to it.
    const string name("Rajat");
    unpack(std::forward_as_tuple(name, 42));  // unpack must expect
    //unpack(std::forward_as_tuple(string("Rajat"), 42));  // unpack must expect
    // name by lvalue and age by rvalue reference

    return 0;
}
