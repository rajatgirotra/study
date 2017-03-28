// Copyright (C) 2015 by RajatGirotra
// read num.cpp first

// Here we'll show how to read and write data members
// Also we'll show separately how to add properties
#include <boost/python.hpp>
#include <string>
#include <iostream>

using std::string;
using std::cout;
using std::endl;

class Data {
 public:
    // C'tor must be public if you want to expose it
    explicit Data(string arg) : name(arg), value() {}
    string name;  // members must be public if you want to expose them
    int value;
};

class Property {
 private:
    int seconds;
 public:
    void set(int hrs) { seconds = hrs * 3600; }
    int get() const { return seconds/3600; }
    void set2(double d, bool b) {
        cout << "d: " << d << "\t b: " << b << endl;
    }
};

BOOST_PYTHON_MODULE(member_property) {
    boost::python::class_<Data>("data", boost::python::init<string>())
        .def_readonly("name", &Data::name)  // ReadOnly attribute
        .def_readwrite("value", &Data::value);  // Read write attribute

    boost::python::class_<Property>("property")
         // Create a new read only property
        .add_property("roHours", &Property::get)
        // Create a read-write property
        .add_property("hours", &Property::get, &Property::set)
        // Create a read-write property with more than 1 argument
        .def("set2", &Property::set2);
        // Cant figure out how to make this work.
}


/* Next read base_derived.cpp */
