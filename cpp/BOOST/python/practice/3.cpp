#include <iostream>
#include <boost/python.hpp>
#include <vector>
#include <string>
using namespace std;
namespace py = boost::python;

class Fruit {
    public:
       string names[7];
       Fruit() : names{"Apple", "Banana", "Peach", "Orange", "Chickoo", "Pear", "Pineapple"} {}

       const string* begin() const noexcept { return &names[0]; }
       const string* end() const noexcept { return &names[7]; }
};

BOOST_PYTHON_MODULE(practice_3_ext) {
    py::class_<Fruit>("Fruit")
//	.add_property("names", py::range(&Fruit::begin, &Fruit::end));
	 .def("__iter__", py::range(&Fruit::begin, &Fruit::end));

    // see 3.py to see difference in usage between add_property() and def()
}
