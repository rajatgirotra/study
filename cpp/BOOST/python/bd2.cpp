// Copyright (C) 2015 by RajatGirotra

// Read base_derived.cpp first
#include <boost/python.hpp>
#include <iostream>

using std::cout;
using std::endl;

// This is same as base_derived.cpp except
// that we only expose three free functions and play
// with those
class Base {
 private:
    int data;
 public:
    explicit Base(int arg = -1) : data(arg) {}
    virtual ~Base() {}
    
    int getValue() const { return data; }
    virtual void setValue(int arg) { data = arg; }
};

class Derived : public Base {
 public:
    explicit Derived(int arg = -1) : Base(arg) {}
    virtual ~Derived() {}
    virtual void setValue(int arg) { Base::setValue(arg * 5); }
};

// Free function
void b(Base* base) {
    cout << "void b(Base*) called" << endl;
}

void d(Derived* derived) {
    cout << "void d(Derived*) called" << endl;
}

// A function which returns a pointer must specify
// a manage policy to handle the destruction of the object
// Otherwise we get an error during compilation
Base* factory() {
    cout << "Base* factory() called" << endl;
    return new Derived;
}



BOOST_PYTHON_MODULE(bd2) {
    boost::python::class_<Base>("Base", boost::python::init<int>())
        .def("getValue", &Base::getValue)
        .def("setValue", &Base::setValue);
    
    // Tell boost python that Derived subclasses Base
    // Boost will automatically expose what Base is exposing.
    boost::python::class_<Derived, boost::python::bases<Base>>
        ("Derived", boost::python::init<int>());

    // Expose the three functions
    boost::python::def("b", b);
    boost::python::def("d", d);
    boost::python::def("factory", factory,
                       boost::python::return_value_policy
                       <boost::python::manage_new_object>());
}

/*
Next we'll see how to write the base class in C++
and override it in python.

See override.cpp
*/
