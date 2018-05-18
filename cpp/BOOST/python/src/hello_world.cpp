//
// Created by rajatgirotra on 18/5/18.
// first class
#include <boost/python.hpp>
#include <iostream>
using namespace std;

const char* greet() {
     return "Hello Greeting!uit";
}

// Creating a python module is really straight-forward
BOOST_PYTHON_MODULE(hello_ext)  { // hello_ext is the name of the module
    using namespace boost::python;
    def("greet", greet);
    // create a module level function with def()
}

// see hello_world.py and world.cpp next