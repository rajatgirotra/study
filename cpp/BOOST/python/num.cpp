// Copyright (C) 2015 by RajatGirotra

// read hello.so first
#include <boost/python.hpp>
#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

struct Num {
    Num() {}
    void set(int pArg) { value = pArg; }
    int get() const {
        // When called from python. cout will also be output
        // so dont get confused where the hell is this output coming from
        cout << "Returning value " << endl;
        return value;
    }
    
 private:
    int value;
};

BOOST_PYTHON_MODULE(num) {
    boost::python::class_<Num>("Num")
        .def("set", &Num::set)
        .def("get", &Num::get);
}

        
// read member_property.cpp next
