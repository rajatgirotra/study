#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wuseless-cast"
#pragma GCC diagnostic ignored "-Wold-style-cast"
#pragma GCC diagnostic ignored "-Wshadow"
#pragma GCC diagnostic ignored "-Wpedantic"

#include <nanobind/nanobind.h>
#include <nanobind/stl/string.h>
#include <print>

namespace nb = nanobind;
using namespace nb::literals;

int add(int a, int b) { return a + b; }

struct Dog {
    std::string name{};

    // Dog(std::string arg) : name(std::move(arg)) {}

    void bark() const noexcept {
        std::println("{} says Woof!! Woof!!", name);
    }
};

NB_MODULE(ext_1, m) { // the name ext_1 must match the nanobind_add_module() in cmake.
    // m.def("add", &add);
    // export a function with arguments and help(docstring)
    // the first argument is the name of the function in python, the second argument is the address of some function to call,
    // the 3rd argument onwards are the function parameters and the docstring. the second argument could be address of any function.
    m.def("add", &add, "a"_a, "b"_a = 1, "simple function to add two numbers");
    m.attr("some_variable") = 42; // export a variable

    // export a class together with its interface.
    nb::class_<Dog>(m, "Dog")
    .def(nb::init<>()) // default ctor
    .def(nb::init<std::string>())
    .def("bark", &Dog::bark)
    .def_rw("name", &Dog::name); // make name attribute read write
}
// Look at the nanobind documentation for binding class constructors, methods, member variables, static varibale,
// static member functions etc.
// .def(), .def_ro(), .def_rw(), .def_prop_ro(), .def_prop_rw(), .def_static(), .def_ro_static(), .def_rw_static()
// .def_prop_ro_static(), .def_prop_rw_static()

#pragma GCC diagnostic pop