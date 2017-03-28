// Copyright (C) 2016 by RajatGirotra

// Read call_method_2.cpp first,
// std::shared_ptr work just as well as boost::shared_ptr

#include <boost/python.hpp>
#include <boost/utility.hpp>
#include <iostream>
#include <string>
#include <cstring>
#include <typeinfo>
#include <memory>

using std::string;
using std::cout;
using std::endl;
using std::shared_ptr;
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
BOOST_PYTHON_MODULE(call_method_3) {
    python::def("is_base", is_base);

    python::class_<shared_ptr<const char>>("spcc")
        .add_property("value", get_value);

    python::class_<Base, Base_callback, boost::noncopyable>("Base")
        .def("class_name", &Base_callback::base_name);

    // python::register_ptr_to_python< shared_ptr<const char> >();
}


// At this point, read hello_ext.cpp through member_property.cpp
// All these classes are fairly trivial and tell you how to use the class_ interface to define functions, and attribute.
/*
  Basically, .def() is used to define a functions.
  .def_readonly() is used to define a read-only attribute
  .def_readwrite() is used to define a read-write attribute
  .staticmethod() is used to define a static method.
  .class_<>("className", "docString")
   template <Init>
  .class_<>("className", "docString", Init) are used to define c'tor on the class
  template <Init>
  def(Init) is used to define multiple c'tors, if available

  .add_property("name", Getter& getter, Setter& setter) - is used to define a property (attribute) which you can get and set
  Also set is optional.
  .add_static_property() --> same as above, but used to create a static property.

  Use: boost::python::no_init if you dont want to expose any c'tor. So object cannot be created from python.
 
  Then you have a couple of methods to support pickling and unpickling.
*/
