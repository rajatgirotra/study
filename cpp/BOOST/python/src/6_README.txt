You really dont need to read this unless you want to understand the internals or write your own call policy.
Better is to move on to some hands on Boost.Python code.

CallPolicies Concepts
---------------------

CallPolicies are set of boost.python classes used to specialize the behavior of the generated wrapper objects (around C++ callable objects).
These wrapper objects are python callable.

You can specialize three behaviors:

1) precall - This concept is used to do any special argument tuple handling before the wrapped c++ callable is invoked.
If X is some CallPolicy, then X.precall(a) --> must return a boolean, where "a" is the argument list.
If it returns false, then PyErr_Occurred() != 0 should also hold, where PyErr_Occurred() is defined as part of Python/C API.

2) result_convertor - This concept is used to define the return value type of the python callable. It is a model of ResultConvertorGenerator
and is a simple metafunction.

3) Postcall - This concept is used to do any special tuple argument and return value management after the C++ callable in invoked.
If X is some CallPolicy, then X.postcall(a, r) --> must return a PyObject*,  ie a python accessible object.
If error, PyErr_Occurred() != 0 should hold and you should return 0.

4) extract_return_type - This is a concept that is used to extract the return value type from a given signature type.
Very simple metafunction. Don't think about it much and we'll get to it shortly.


If you see the with_custodian_and_ward<> class, you'll see a "static void precall()" method which does argument processing

Dereferencable Types
-------------------

Dereferencable types are types that can be used like a pointer. Eg: smart pointers
If you have some C++ type T and object of type T called x,
then get_pointer(x), should return pointee<T>::type*
eg T could be unique_ptr, shared_ptr etc. and boost.python defines pointee as:
template <typename T>
struct pointee {
    typedef typename T::value_type type;
};
Basically, boost.python uses get_pointer(x), when converting a c++ object to python object, and if these C++ objects are wrapped in smart pointers, they can be used seamlessly with boost.python.
See boost_src/include/boost/python/convertor/shared_ptr_to_python.hpp and boost_src/include/boost/get_pointer.hpp

When you have time, read about boost.python.register_ptr_to_python function, which is related to the above.
Also we need to check on what to do when writing my own special custom smart pointer class.


Extractor
---------
boost.python has extractors which are used to extract c++ objects from python objects. and mostly used in the
from_python() conversions. If there is some Extractor X defined in boost.python and "a" is some python object,
then
1) X::execute(a) --> should return the C++ object extracted.
2) a.ob_type -->  Must be a PyTypeObject* type held the the PyObject "a". So a PyObject holds ob_type which is PyTypeObject*

If you see the with_custodian_and_ward<> class, you'll see a "static void precall()" method which calls a static method
"execute()" on a Extractor class to fetch the C++ object from the python object.


HolderGenerator
--------------

HolderGenerator is a unary metafunction class which returns types which can hold instances of the metafunction class template argument.
So if G is a holder generator, and X is some type, then G::apply<X>::type is a C++ wrapper type which can hold instances of X.
These wrapper types are nothing but some concrete subclass of instance_holder.
We'll see how and where is a HolderGenerator used.


ResultConvertor & ResultConvertorGenerator
-----------------------------------------

A ResultConvertor for a type T is a type whose instances can be used to convert C++ return values of type T to_python.
So if some C++ function returns a value of type R, and if C is a ResultConvetor for type R, then instances of C can be used
to convert values of types R to_python().

Boost.python has a registry of ResultConvertors. A ResultConvertorGenerator is a metafunction class which takes a type R, and
returns you a ResultConvertor for that type. So, if G is a ResultConvetorGenerator, then

G::apply<R>::type is C.

C c; // to create an instance of ResultConvertor
c(r); // where r is return value from some function of type R. c(r) will return a PyObject* or 0, in which case PyErr_Occurred() should return non zero
c.get_pytype() - Returns a const PyTypeObject*

/* Please read list.cpp */
