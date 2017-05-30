// Copyright (C) 2015 by RajatGirotra

// Tuple assignment operator =
#include <iostream>
#include <tuple>
#include <string>
using std::tuple;
using std::cout;
using std::endl;

struct A {
    A() {
        cout << "A c'tor" << endl;
    }

    A(const A&) {
        cout << "A copy c'tor" << endl;
    }

    A(A&&) {
        cout << "A move c'tor " << endl;
    }

    ~A() {
        cout << "A d'tor" << endl;
    }

    A& operator = (const A&) {
        cout << "A copy assignment" << endl;
    }

    A& operator = (A&&) {
        cout << "A move assignment" << endl;
    }
};
    
int main(int argc, char *argv[]) {
    // Case 1. You have an lvalue tuple object
    // operator = will do copy assignments as expected.
    tuple<int, char, bool> t1(10, 'a', true);
    tuple<int, char, bool> t2 = t1;
    cout << "int: " << std::get<0>(t2) << "  char: " << std::get<1>(t2)
         << "  bool: " << std::boolalpha << std::get<2>(t2) << endl;

    // Case 2. You have an rvalue tuple object.
    // operator = will behave like calling std::forward<> for each type.
    // resulting in move c'tor/assignment being called if the type
    // supports move c'tor/assigments.
    {
    tuple<A> t3 = std::make_tuple(A()); // make_tuple returns tuple<int&&>
    }
    cout << "OR" << endl;
    A a;
    tuple<A> t4 = std::make_tuple(a); // make_tuple returns tuple<int&>
    // in case above, argument to make_tuple is lvalue,
    // so std::forward will end up calling copy c'tor.

    // I am not showing other Cases where implicit conversions happen
    // like from tuple<long, char> to tuple<int, char>.
    // These are fairly straight forward.
    return 0;
}
