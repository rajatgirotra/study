#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wuseless-cast" // all these to silence some warnings in nanobind headers
#pragma GCC diagnostic ignored "-Wold-style-cast"
#pragma GCC diagnostic ignored "-Wshadow"
#pragma GCC diagnostic ignored "-Wpedantic"

#include <nanobind/nanobind.h>
#include <nanobind/stl/string.h>
#include <print>

namespace nb = nanobind;
using namespace nb::literals;

struct Dog {
    std::string name{};

    // Dog(std::string arg) : name(std::move(arg)) {}

    void bark() const noexcept {
        std::println("{} says Woof!! Woof!!", name);
    }
};

void nothing_function() {
    std::println("this function does nothing");
}

NB_MODULE(ext_2, m) { // the name ext_1 must match the nanobind_add_module() in cmake.
    // export a class together with its interface.
    nb::class_<Dog>(m, "Dog")
    .def(nb::init<>()) // default ctor
    .def(nb::init<std::string>())
    .def("bark", &Dog::bark)
    .def_prop_rw("name",
        [](const Dog& d)-> std::string {return d.name;},
        [](Dog& d, std::string arg) -> void { d.name = arg;},
        nb::for_getter("docstring for getter"),
        nb::for_setter("docstring for setter"))
    .def("__repr__", [](const Dog& d) { return std::string("dog: ") + d.name; }) //override __repr__ so that print(Dog) returns something useful.
    .def("bark_later", []([[maybe_unused]] const Dog& dog) {
        // I want to call nothing_function. but not immediately. I just want to return a reference to that function. I can do it using nb::cpp_function().
            auto callback = [name = dog.name]() {
                std::println("{} says Woof!! Woof!!", name);
            };
        return nb::cpp_function(callback);
    });

}
#pragma GCC diagnostic pop