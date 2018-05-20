//
// Created by rajatgirotra on 18/5/18.
//
#include <boost/python.hpp>
#include <string>
#include <iostream>
using namespace std;

struct Var {
    std::string name;
    double value;
    Var(std::string arg): name(arg) {}
};

/* note that we made the data members above public, which is ok for python but not good for C++ as data members are
 * usually private. To workaround this. keep your data members private, and instead of using def_readonly or def_readwrite
 * use add_property("name", getter, setter). This will expose a python property and also keep your data encapsulated in
 * C++. Let's to it.
 */

class BetterVar {
private:
    std::string name;
    double value;
public:
    BetterVar(std::string arg): name(arg) {}

    // getters
    double getValue() const { return value; }
    std::string getName() const { return name;}

    // setter
    void setValue(double arg) { value = arg; }
};


//expose both classes
BOOST_PYTHON_MODULE(data_member_ext) {
    using namespace boost::python;
    class_<Var>("Var", init<std::string>()).def_readonly("name", &Var::name).def_readwrite("value", &Var::value);

    class_<BetterVar>("BetterVar", init<std::string>()).add_property("name", &BetterVar::getName)
            .add_property("value", &BetterVar::getValue, &BetterVar::setValue);
}

// Next lets see how derived classes work with Boost Python. See base_derived.cpp
