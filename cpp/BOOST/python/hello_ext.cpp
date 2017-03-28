// Copyright 2015 RajatGirotra

// First file in this file.

#include <boost/python.hpp>

const char* greet() {
    return "Hello World";
}

BOOST_PYTHON_MODULE(hello_ext) {  // name of the module
    using boost::python::def;
    def("greet", greet);  // python function name, followed by c++ function-name
}

// Please read world.cpp next
