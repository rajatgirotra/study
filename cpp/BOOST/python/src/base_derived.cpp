//
// Created by rajatgirotra on 18/5/18.
//
#include <boost/python.hpp>
#include <string>
#include <iostream>
using namespace std;

class Base {
private:
    int data;
public:
    Base(int arg) : data(arg) {}

    static void display() {
        cout << "Base\n";
    }

    void set(int newValue) {
        data = newValue;
    }

    int get() const {
        return data;
    }

    // calling the derived version of f() from python is also trivial.
    virtual void f() { cout << "f() from Base\n"; }

    virtual ~Base() {}
};


class Derived : public Base {
    double value;
public:
    Derived(double d, int i) : Base(i), value(d) {}

    void f() {
        cout << "Overriding f() from Base\n";
    }

    double dbl_value() const { return this->value; }

};

void b(Base*) {
    cout << "In b(Base*)\n";
}

void d(Derived*) {
    cout << "In d(Derived*)\n";
}

// Since we will wrap this function later, we want someone to manage ownership of this object.
// We can use the Boost python Policies to choose between.
Base* factory() {
    return new Derived(3.5, 10);
}

BOOST_PYTHON_MODULE(base_derived_ext) {
    using namespace boost::python;
    // class_ second template parameter is bases -  where you can specify one or more base classes of the
    // first template argument. Specifying a Base class allows all Base class members to be accessed by Derived
    // in python too. The other advantage is that Derived objects can be returned from C++ to any python functions
    // that accept a pointer or reference to Base. Moreover, these Derived objects can be passed to any functions
    // in python which accepts Base or Derived pointer or reference.
    class_<Base>("Base", init<int>()).def("display", &Base::display).staticmethod("display")
            .add_property("value", &Base::get, &Base::set).def("f", &Base::f);
    class_<Derived, bases<Base>>("Derived", init<double, int>()).def("dbl_value", &Derived::dbl_value);

    // Let's create wrappers for b, d, and factory
    def("b", b);
    def("d", d);

    // In factory method, we are using new to create an instance of Derived. Who should manage that instance?
    // When should it be released? All that is decided by a call policy. Here we using a simple call policy
    // "return_value_policy<manage_new_object>()" which means that Python will manage it internally.
    // we'll see in detail call policies in a bit.
    def("factory", factory, return_value_policy<manage_new_object>());
}

// We need to debug why b() & d() are not callable from python. We'll do that later.
// see base_derived.py then abstract.cpp next

// You really dont need to expose the Derived class to python if you will not directly create an instance of it.
// If you will always use the factory() function to create instances of the derived classes and always call derived
// methods polymorphically, then no need to expose it.