/*
Perhaps the most important use of std::reference_wrapper<> is to wrap a c++ callable
and then pass it around as argument to functions. and then finally call it using the
std::reference_wrapper::operator() function.

template <typename... Args> 
typename result_of<type& (Args&&...)>::type
operator() (Args&&...args) const;

You can wrap a c++ callable or a data member of a class too.
See below how u can wrap callables and data members of classes, and them call them
using arguments.
*/

#include <iostream>
#include <functional>
#include <string>
#include <typeinfo>
#include <memory>
#include <cxxabi.h>
using namespace std;

string demangle(const char* mangled_name) {
    int status = -1;
    char* realname = abi::__cxa_demangle(mangled_name, 0, 0, &status);
    if (status == 0) {
        string demangled_name(realname);
        free(realname);
        return demangled_name;
    } else {
        string demangled_name(mangled_name);
        return demangled_name;
    }
}

// simple function
string hello(int a, int b) {
    return "Hello numbers " + std::to_string(a) + " " + std::to_string(b);
}

// function object
struct fo {
    int operator()(const int& a, const int& b) {
        return a+b;
    }
};

// pointer to function
string (*poHello)(int a, int b) = &hello;

struct operations {
    int a;
    int b;
    operations(int x, int y) : a(x), b(y) {
    }

    int mul() const {
        return a*b;
    }
};

// pointer to data member
int operations::*poA = &operations::a;
// pointer to member function
int (operations::*poMemFunc)() const = &operations::mul;


int main() {
    // function
    auto ref_fun = std::reference_wrapper<string(int, int)>(hello);
    // a shorter way of creating a reference_wrapper is to use std::ref()
    auto ref_fun2 = std::ref(hello);  // ref_fun and ref_fun2 are exactly same.
    cout << ref_fun(10, 20) << endl;
    cout << ref_fun2(10, 20) << endl;

    // function object
    fo fo_obj;
    auto ref_fo = std::ref(fo_obj);
    cout << ref_fo(2, 3) << endl;

    // pointer to function
    auto ref_ptr_to_func = std::ref(poHello);
    cout << ref_ptr_to_func(100, -100) << endl;

    // pointer to member function
    operations o {40, 3};
    std::unique_ptr<operations> oPtr(new operations(3, 9));
    auto ref_ptr_to_mem_func = std::ref(poMemFunc);
    cout << ref_ptr_to_mem_func(o) << endl;  // object
    cout << ref_ptr_to_mem_func(&o) << endl;  // or pointer to object
    cout << ref_ptr_to_mem_func(oPtr) << endl; // or smart pointer to object, all work

    auto ref_ptr_to_data_mem = std::ref(poA);
    cout << ref_ptr_to_data_mem(o) << endl;
    cout << ref_ptr_to_data_mem(&o) << endl;
    cout << ref_ptr_to_data_mem(oPtr) << endl;
    return 0;
}
