// Copyright (C) 2016 by RajatGirotra

// Read call_method.py
// Here we use a boost:sp<> to wrap the const char* which works.
#include <boost/python.hpp>
#include <boost/utility.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <iostream>
#include <string>
#include <cstring>
#include <typeinfo>

using std::string;
using std::cout;
using std::endl;
using boost::shared_ptr;
using boost::make_shared;
namespace python = boost::python;

// Base class
struct Base {
     Base() {
        cout << "Base::Base()" << endl;
    }
    virtual shared_ptr<const char>  class_name() const {
        cout << "Base::class_name() called" << endl;
        const char* po_arr = new char[5] {'B', 'a', 's', 'e', '\0' };
        return shared_ptr<const char>(po_arr);
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

    shared_ptr<const char> class_name() const {
        cout << "Base_callback::class_name() called" << endl;
        return python::call_method<shared_ptr<const char>>(m_self,
                                                            "class_name");
    }

    shared_ptr<const char> base_name() const {
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
    return !std::strcmp(base->class_name().get(), "Base");
}

const char* get_value(const shared_ptr<const char>& spcc) {
    return spcc.get();
}

// define python module
BOOST_PYTHON_MODULE(call_method_2) {
    python::def("is_base", is_base);

    python::class_<shared_ptr<const char>>("spcc")
        .add_property("value", get_value);

    python::class_<Base, Base_callback, boost::noncopyable>("Base")
        .def("class_name", &Base_callback::base_name);

    // python::register_ptr_to_python< shared_ptr<const char> >();
}

// Next is call_method_3.cpp. The only diff is that we try to use std::shared_ptr instead of boost pointers.
