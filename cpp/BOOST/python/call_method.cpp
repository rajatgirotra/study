// Copyright (C) 2016 by RajatGirotra

// Please read 3_README.txt

#include <boost/python.hpp>
#include <boost/utility.hpp>
#include <iostream>
#include <string>
#include <cstring>
#include <typeinfo>

using std::string;
using std::cout;
using std::endl;
namespace python = boost::python;

// Base class
struct Base {
    Base() {
        cout << "Base::Base()" << endl;
    }
    virtual const char* class_name() const {
        cout << "Base::class_name() called" << endl;
        return "Base";
    }

    virtual ~Base() {
        cout << "Base::~Base()" << endl;
    }
};

// Wrapper class
struct Base_callback : public Base {
    explicit Base_callback(PyObject* py_obj): m_self(py_obj) {
        cout << "Base_callback::Base_callback()" << endl;
    }

    const char* class_name() const {
        cout << "Base_callback::class_name() called" << endl;
        return python::call_method<const char*>(m_self, "class_name");
    }

    const char* base_name() const {
        cout << "Base_callback::base_name() called" << endl;
        return Base::class_name();
    }

    ~Base_callback() {
        cout << "Base_callback::~Base_callback()" << endl;
    }

 private:
    PyObject* m_self;
};

bool is_base(Base* base) {
    cout << "is_base() called with: " << typeid(*base).name() << endl;
    return !std::strcmp(base->class_name(), "Base");
}

// define python module
BOOST_PYTHON_MODULE(call_method) {
    python::def("is_base", is_base);

    python::class_<Base, Base_callback, boost::noncopyable>("Base")
        .def("class_name", &Base_callback::base_name);
}

// Next is call_method_2.cpp
