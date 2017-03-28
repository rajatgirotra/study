// Copyright (C) 2015 by RajatGirotra
#include <boost/python.hpp>
#include <boost/noncopyable.hpp>
#include <iostream>
#include <memory>

using std::cout;
using std::endl;
using boost::python::def;
using boost::python::class_;
using boost::python::return_value_policy;
using boost::python::manage_new_object;
using boost::python::wrapper;
using boost::python::init;
using boost::python::pure_virtual;

class Base {
 public:
    Base() {}
    virtual ~Base() {}

    virtual int f() = 0;
};

// To override this class in python and not to intrusively make any
// changes to Base class, define a new class which derives from Base
// and from boost::python::wrapper

class BaseWrapper : public Base, public wrapper<Base> {
 public:
    virtual ~BaseWrapper() {}

    int f() override {
        return this->get_override("f")();
    }
};


// Before defining the BOOST_PYTHON_MODULE, lets understand the boost::python::class_ template class
/*
  class_ is a template class defined by boost.python
  class_<T, Bases, HeldType, Noncopyable>
  Only the first parameter is mandatory. Others are optional and can be secified in any order.

Creating an object of class_ creates an instance of a python class for the C++ type specified by T.

1) T : You already know from above
2) Bases: If T derives from a another class which has already been exposed to python, then specify here
          using bases<BaseTypeOfT>
3) HelpType: This is the actual type held by a python object wrapping a type T; and can be either T (default)
   or a type derived from T. Or a De-referenceable type of T (like auto_ptr or shared_ptr)
4) Noncopyable: boost::noncopyable, sometimes the type T cannot be instantiated (may be it an ABC or
   (does not have any public c'tors). In such cases, we have to use non-copyable.
*/

BOOST_PYTHON_MODULE(override) {
    class_<BaseWrapper, std::shared_ptr<BaseWrapper>, boost::noncopyable>
             ("BaseWrapper", "DocStringForBaseWrapper")
             .def("f", pure_virtual(&BaseWrapper::f));
}
