// Copyright (C) 2015 by RajatGirotra
// Lets study about various traits classes

// has_virtual_destructor<T>::value
// True if class has virtual destrcutor or a sub class which
// derives from a class having a virtual destrcutor

// is_abstract<T>::value
// True if a class has a pure virtual function

// is_constructibale<typename T, typename... Args>
// tells if class T can be constrcuted with arguments Args
#include <iostream>
#include <type_traits>
using std::cout;
using std::endl;

struct A {
    A(int, int) {}
};

int main() {

    cout << std::boolalpha;
    // default int is always constructible
    cout << "is_constructible<int> : " << std::is_constructible<int>::type::value << endl;
    // int can be constructed from a float.
    cout << "is_constructible<int, float> : " << std::is_constructible<int, float>::type::value << endl;
    // int CANNOT be constructed from two floats.
    cout << "is_constructible<int, float, float> : " << std::is_constructible<int, float, float>::type::value << endl;

    // Rest is trivial
    cout << "is_constructible<A> : " << std::is_constructible<A>::type::value << endl;
    cout << "is_constructible<A, int> : " << std::is_constructible<A, int>::type::value << endl;
    cout << "is_constructible<A, int, int> : " << std::is_constructible<A, int, int>::type::value << endl;
    cout << "is_constructible<A, float, double> : " << std::is_constructible<A, float, double>::type::value << endl;
    return 0;
    
}
