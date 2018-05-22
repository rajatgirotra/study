boost::python::object

Boost.Python defines an object class which is a wrapper over a pointer to PyObject*. It then defines a number of derived
classes for a number of python builtin types like
1) boost::python::list for list
2) boost::python::dict for dict
3) boost::python::tuple for tuple
4) boost::python::str for str

etc. Each of these derived classes have a number of methods corresponding to their python counterparts. Example:

1) boost::python::str(1) gives "1"
2) boost::python::dict.keys() gives the dictionary keys.
3) boost::python::make_tuple() for creating a python tuple.
All these methods return nothing but a boost::python::object. Example:

void f(boost::python::str name)
{
    boost::python::object n2 = name.attr("upper")();   // NAME = name.upper()
    boost::python::str NAME = name.upper();            // better
    boost::python::object msg = "%s is bigger than %s" % make_tuple(NAME,name);
}

Infact what you expose using class_<> is nothing but a boost::python::object. To get an attribute of an object class into
a C++ type, use boost::python::extract, example:

double d = boost::python::extract<double>(o.attr("length")); // will throw if extraction is not possible.


Python doesnt have enum types. But you can create enum types using C++ defined enums. Example:

enum choice { red, green};

BOOST_PYTHON_MODULE(module_ext) {
    using namespace boost::python;
    enum_<choice>("choice").value("red", red).value("blue", blue);
}

Use:
boost::python::object o(boost::python::handle<>(pyobj)); // for o to manage a pointer to PyObject*, will not call PY_INCREF
boost::python::object o(boost::python::handle<>(boost::python::borrowed(pyobj))); // will call PY_INCREF

/*
Please read 6_README.txt
*/