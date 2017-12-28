/*
 * C++0x11 also provides another keyword decltype(x) to deduce the type of an expression at compile time.
 *
 * Rule: Use auto when you are initializing a variable.
 * Use decltype(x) when you want to use the type of the variable in some way.
 */

#include <iostream>
#include <string>
#include <typeinfo>
#include <vector>
#include <cxxabi.h>
#include <cassert>
using namespace std;

string demangle(const char* mangled_name) {
    auto status {0};
    auto realname = abi::__cxa_demangle(mangled_name, 0, 0, &status);
    assert(status == 0 && realname != nullptr);
    return realname;
}

int main() {
    decltype(5) x = 10; //x will be of type int as 5 is an int. Also x is a value type.
    decltype(x) y = 10; //y will also be of type int as x is int. Also y is value type.
    x++; y--;
    cout << "x: " << x << endl;
    cout << "y: " << y << endl;

    auto& z = y; //z is of type int and it is a reference type.
    z--;

    cout << endl;
    cout << "y: " << y << endl;
    cout << "z: " << z << endl;

    //decltype(z) a; //Error. Since z is a reference type, a will be a reference type, you must tie it to some piece of memory.
    decltype(z) a = z; //a is now of type int and it is a reference_type as z is a reference type.
    a--;
    cout << endl;
    cout << "y: " << y << endl;
    cout << "z: " << z << endl;
    cout << "a: " << a << endl;
 
    auto rajat = z;
    rajat++;
    z--;
    cout << endl;
    cout << "y: " << y << endl;
    cout << "z: " << z << endl;
    cout << "a: " << a << endl;
    cout << "rajat: " << rajat << endl;

    decltype(0) p; //this is ok. since 0 is a value_type, p will also be of value_type and of type int and will hold garbage.
    cout << endl;
    cout << "p: "<< p << endl;

    vector<int> v(5);
    auto f = v[0];  //since v[0] returns an int, f will be of type int, and as you can clearly see, it is of value_type.
    cout << "f (should be 0): " << f << endl;

    //decltype(v[0]) g; //Error. Note that operator[] always returns a reference, so g is a reference type, so here you must tie it to some reference.

    
    decltype(v[0]) ab = z; //Note this does not mean that v[0] is z. ab is only of type v[0], it does not reference v[0] in any way.
    cout << "v[0] (should be 0): "<< v[0] << endl;
    cout << "ab (should be 6): "<< ab << endl;

    //decltype(v[0]) h = 1; //Error. Very trivial. v[0] returns a int& and right hand side is const int&. This will work if you make your vector const as operator[] will return const int&

    return 0;
}
