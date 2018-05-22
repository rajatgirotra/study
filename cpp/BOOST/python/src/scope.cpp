/* boost::python::scope() class is used to control the scope in which wrapped classes and functions are defined in the
 * BOOST_PYTHON_MODULE. By default, the scope if the global module scope. When you create another scope() object, all
 * subsequent wrapped classes and functions will by default be defined that new scope. When the scope object lifetime will end
 * the scope will be reverted back to the old scope
 * Let's see in an example
 */
#include <boost/python.hpp>
#include <iostream>
#include <string>
using namespace std;

class X {
public:
    void f() { cout << "X::f()\n";}

    // Y is in scope of X
    struct Y { int g() { cout << "X::Y::g()\n"; return 100;} };
};


BOOST_PYTHON_MODULE(scope_ext) {
    using namespace boost::python;
    // define an new attribute at module scope
    scope().attr("yes") = 1;

    {
        //  Create a new scope for class X
        scope x_scope = class_<X>("X").def("f", &X::f);
        // now the scope is X. expose Y inside the scope of X
        class_<X::Y>("Y").def("g", &X::Y::g);

    }
    // scope ended. again the default scope is global module scope. Create another attribute
    scope().attr("no") = 0;
}

/* Please read call_method.cpp and call_method.py next */

