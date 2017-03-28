// Copyright 2015 RajatGirotra

// Please read hello_ext.cpp

#include <boost/python.hpp>
#include <string>

struct Greeting {
    std::string name;
    void set(std::string pName) { name = pName; }
    std::string get() const { return name; }
};

BOOST_PYTHON_MODULE(world) {  // world is the python module name
    // Greeting is the class name you are exporting
    // greeter is the name of the class in python
    boost::python::class_<Greeting>("greeter")
        //  greet is the function name in python which maps to get() function
        .def("greet", &Greeting::get)
        .def("setGreeting", &Greeting::set);
}

// Next : hello.cpp
