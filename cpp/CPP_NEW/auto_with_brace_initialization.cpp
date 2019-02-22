#include <iostream>
#include <typeinfo>
#include <cxxabi.h>
#include <string>
using namespace std;

string demangled_name(const char* mangled_name) {
    int status {};
    auto demangle = abi::__cxa_demangle(mangled_name, 0, 0, &status);
    if(!status) {
        string value(demangle);
        return value;
        free(demangle);
    }
    throw std::runtime_error("Error in name demangling");
}
int main() {
    auto x = 27;
    auto y(27);
    auto z = {27};
    auto w {27};

    decltype(100) a = 100;

    cout << "auto x = 27;   x = " << demangled_name(typeid(x).name()) << endl;
    cout << "auto y(27);    y = " << demangled_name(typeid(y).name()) << endl;
    cout << "auto z = {27}; z = " << demangled_name(typeid(z).name()) << endl;
    cout << "auto w {27};   w = " << demangled_name(typeid(w).name()) << endl;
    cout << "decltype(100) a = 100;   a = " << demangled_name(typeid(a).name()) << endl;
}