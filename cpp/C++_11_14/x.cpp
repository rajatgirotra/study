#include <iostream>
#include <string>
#include <tuple>
#include "43.h"
using namespace std;

template <typename T>
struct get_type {
    static const string value;
};

template<typename T>
struct get_type<T&&> {
    static const string value;
};

template<typename T>
struct get_type<T&> {
    static const string value;
};

template<typename T>
struct get_type<T*> {
    static const string value;
};

template <typename T>
const string get_type<T>::value = "POD Type";

template <typename T>
const string get_type<T&>::value = "lvalue reference type";

template <typename T>
const string get_type<T&&>::value = "rvalue reference type";

template <typename T>
const string get_type<T*>::value = "Pointer type";

int main() {
    string name("Rajat");
    string&& s = string("Rajat"); 
    // string&& s1 = name;
    auto&& s1 = name;
    cout << demangle(typeid(s1).name()) << endl;
    cout << typeid(const int&).name() << endl;
    cout << get_type<decltype(s1)>::value << endl;
    cout << get_type<decltype(s)>::value << endl;
    cout << get_type<decltype("Rajat")>::value << endl;

    //auto&& x1 = std::get<0>(tuple<const int&, double&&>(10, 2.5));
    auto y = tuple<const int&, double&&>(10, 2.5);
    auto&& x1 = std::get<0>(std::move(y));
    cout << endl;
    cout << get_type<decltype(x1)>::value << endl;

    tuple<int, double&&> t3(100, 23.25);
    cout << "a: " << get_type<std::tuple_element<0, decltype(t3)>::type>::value << endl;
    return 0;
}
