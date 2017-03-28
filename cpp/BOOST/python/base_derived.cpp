// Copyright (C) 2015 by RajatGirotra

// Read member_property.cpp first
#include <boost/python.hpp>
#include <iostream>

using std::cout;
using std::endl;

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

BOOST_PYTHON_MODULE(base_derived) {
    boost::python::class_<Base>("Base", boost::python::init<int>())
        .def("getValue", &Base::getValue)
        .def("setValue", &Base::setValue);
    
    // Tell boost python that Derived subclasses Base
    // Boost will automatically expose what Base is exposing.
    boost::python::class_<Derived, boost::python::bases<Base>>
        ("Derived", boost::python::init<int>());
}

// Read bd2.cpp next
