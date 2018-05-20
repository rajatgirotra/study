//
// Created by rajatgirotra on 18/5/18.
//
#include <boost/python.hpp>
#include <iostream>
#include <string>
using namespace std;

class Cruel {
    double m_value;
    bool m_decide;
public:
    // No arg c'tor
    Cruel() : m_value(-100), m_decide(true) {

    }

    // One arg c'tor
    Cruel(double val) : m_value(val), m_decide(false) {}

    // Two argument c'tor
    Cruel(double val, bool decide) : m_value(val), m_decide(decide) {}

    double get_value() const { return m_value;}
    bool get_decision() const { return m_decide;}
};

// Expose an abstract class also, so python will give an error if we try to create an object of this class.
class Abstract {
public:
    static int getValue() { return 100;}
};

BOOST_PYTHON_MODULE(cruel_ext) {
    using namespace boost::python;
    // c'tor can be specified as second argument to class_ c'tor or later in def() member function.
    // We will now explicitly need to expose the default c'tor too.
    class_<Cruel>("value_decider", init<double>()).def(init<double, bool>()).def("get_value", &Cruel::get_value)
            .def("get_decision", &Cruel::get_decision).def(init<>());

    //Note this syntax - Since getValue() is static, we have to additionally call staticmethod() on class_.
    //boost::python::no_init means you are deliberately not exposing any c'tors
    class_<Abstract>("abstract", boost::python::no_init).def("value", &Abstract::getValue).staticmethod("value");
}

// next we'll see how to wrap data members. See cruel.py and data_member.cpp next
