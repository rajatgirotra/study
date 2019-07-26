/* create a simple function in C++ at module level with a docstring, some arguments, and some keyword arguments (some with default values) */
#include <iostream>
#include <boost/python.hpp>
using namespace std;
using namespace boost::python;
void foo(int x, double y, bool z = false) {
    cout << "foo called with x: " << x << ", y: " << y << ", z: " << std::boolalpha << z << endl;
}

BOOST_PYTHON_FUNCTION_OVERLOADS(foo_overloads, foo, 2, 3);

BOOST_PYTHON_MODULE(practice_1_ext) {
    def("foo", foo, foo_overloads((args("x"), "y", args("z")=false), "documentation for function foo"));
}
