// Copyright 2015 RajatGirotra

/*
Please read world.cpp first
*/

#include <boost/python.hpp>
#include <string>
using std::string;

// Exporting a class with constructors
struct World {
    string name;
    double d1;
    double d2;
    explicit World(const string& arg) : name(arg) {}
    World(const double& d1Arg, double d2Arg) {
        d1 = d1Arg;
        d2 = d2Arg;
    }
    string get() const { return name; }
    void set(string arg) { name = arg; }
};

// Class to expose no c'tors
struct Abstract {
    int getValue() {return 10;}
};

BOOST_PYTHON_MODULE(hello) {
    boost::python::class_<World> ("world", boost::python::init<string>())
        .def(boost::python::init<double, double>())
        .def("get", &World::get)
        .def("set", &World::set);

    // use no_init
    boost::python::class_<Abstract>("abstract", boost::python::no_init)
        .def("value", &Abstract::getValue);
}

// Next : num.cpp
