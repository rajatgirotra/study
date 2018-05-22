/* call_method<> is a family of function templates in Boost.python; they allow C++ code to call Python code. Syntax is very
 * trivial
 * template <typename ReturnType, typename... Args>
 * ReturnType call_method(PyObject* object, const char* function_name, Args...)
 *
 * where object.function_name(Args...) will be called and the return value from Python will be used to convert to ReturnType
 *
 * ReturnType value = boost::python::extract<ReturnType>(object.function_name(Args...));
 */
#include <boost/python.hpp>
#include <boost/noncopyable.hpp>
#include <iostream>
#include <cstring>
using namespace std;

// The class to be exposed
class Base {
public:
    virtual const char* class_name()  const {
        cout << "Base Called\n";
        return "Base";
    }

    virtual ~Base() = default;
};

// The actual HeldType to be passed in class_
class Base_callback : public Base {
private:
    PyObject* m_self;
public:
    // the c'tor should be similar to the base class except that they take one extra argument: PyObject*
    Base_callback(PyObject* arg) : m_self(arg) {}

    virtual const char* class_name() const {
        cout << "Base_callback Called\n";
        auto&& x = boost::python::call_method<boost::python::str>(m_self, "class_name");
        return boost::python::extract<const char*>(x);
    }

    const char* base_name() const { cout << "Base_callback base_name called\n"; return Base::class_name(); }
};

bool is_base(Base* base) {
    if(dynamic_cast<Base_callback*>(base) != nullptr)
        cout << "Object is base_callback type\n";
    else
        cout << "Object is not base_callback type\n";

    return !strcmp(base->class_name(), "Base");
}

const char* call_f(Base* base) {
    return base->class_name();
}

BOOST_PYTHON_MODULE(call_method_ext) {
    using namespace boost::python;

    class_<Base, Base_callback, boost::noncopyable>("Base")
            .def("class_name", &Base_callback::base_name);

    def("is_base", is_base);
    def("call_f", call_f);
}


/* What's happening. When HeldType is a derived type (like Base_callback here), it's ctor must except a PyObject pointer
 * This PyObject* points to an object of type HeldType (ie Base_callback in this case). So If i create an instance of:
 *
 * 1) Base() in my python code, then the PyObject class would hold a Base_callback object. So if is_base(Base()) is called,
 * then Base* in C++ is pointing to a Base_callback object. So m_self in Base_callback actually points to itself. So "class_name"
 * method is called using call_method which calls base_name of m_self which returns "Base".

 * 2) Derived() (where Derived is created in python, then the PyObject* will wrap a Derived object). Note that Derived actually
 * derives from Base_callback.
 *
 * The "class_name" method exposed is actually Base_callback::base_name. So when is_base(Derived()) is called from python,
 * it calls Base_callback::base_name, which calls Base::class_name() which again calls Base_callback::class_name() which
 * calls class_name() on the wrapped PyObject*, ie. class_name() implementation in Derived written in Python.
 *
 * Basically an method in C++ written to accept a Base* will actually be receiving Base_callback* from Python.
 */