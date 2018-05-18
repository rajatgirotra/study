//
// Created by rajatgirotra on 18/5/18.
// Here we will create a python wrapper for a C++ class with a simple getter and setter.

#include <boost/python.hpp>
#include <iostream>
#include <string>
using namespace std;

class Greeting {
    std::string msg;
public:
    void set(std::string arg) { this->msg = arg; }
    std::string get() const { return msg; }

    // If I change the argument type in set() to be a const lvalue reference or
    // If I change the return type in get() to be a const std::string&, i start getting issues. I'll come back in a bit
    // why this is the case. At the moment, we are just passing and return simple copies.
};

BOOST_PYTHON_MODULE(world_ext) {
    using namespace boost::python;
    class_<Greeting>("greeter")
            .def("set_greeting", &Greeting::set).def("greet", &Greeting::get);

    // By default, boost::python exposes the default c'tor always, so here we didnt need to do explicitly.
    // If we didnt have a no arg c'tor, the program would have failed to compile. Let's see next how to expose
    // c'tors.
}

// Please world.py and cruel.cpp next
/*
 * class_ is a template class. We'll see other template parameters soon. Next we'll see how we can add construction
 * information to these wrapper objects.
 */