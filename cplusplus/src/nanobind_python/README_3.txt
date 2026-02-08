In nanobind, you are constantly exchanging information between C++ and Python. This exchange can happen in one of the three ways.

1. type casting
===============
In type casting, nanobind will automatically convert function arguments and return values between python types and C++ types. For example, if you have a cpp function:

vector<int> double_it(vector<int> arg) {
    vector<int> res{arg.size()};
    for(auto i : arg) {
       res.push_back(i * 2);
    }
    return res;
}

then in nanobind, you will need to include the correct header for type casting between cpp vector<int> and python list[int].
#include <nanobind/stl/vector.h>

NB_MODULE(my_ext, m) {
   m.def("double_it", &double_it);
}

nanobind will automatically create the python version of the function "double_it" with a generated docstring, type checks, and (if needed) error reporting.

>>> import my_ext
>>> my_ext.double_it([1, 2, 3])
[2, 4, 6]

The problem with type casting is that it is slow. It involves a type conversion on every call between the c++ and python boundary. Also if you only want to use one value in a big list, you still need to perform the type conversion for the whole list.
Another problem is that this type conversion is only performed once during conversion from python to c++ (converting parameters to c++ types) and from c++ to python (converting return value type to python type). This means if a c++ function accepts a reference parameter and modifies it, the change won't be visible in python. So reference arguments are not supported.

The good part about type casters is that type casters are available for a lot of simple and complex types in C++ so you can use them straight away in many cases. If speed is not an issue, you can definitely stick to type casters.

2. Bindings
===========
nanobind provides bindings, which means it provides explicit Python types for many C++ types. These types can also be created dynamically. Example, if you have C++ like below:

using IntVector = std::vector<int>;
IntVector double_it(const IntVector& in) { ... };

namespace nb = nanobind;
NB_MODULE(my_ext, m) {
   nb::bind_vector<IntVector>(m, "IntVector"); // nb::
   m.def("double_it", &double_it);
}

Any function taking or returning integer vectors will now use the type binding. In the Python session below, nanobind performs an implicit conversion from the Python list [1, 2, 3] to a my_ext.IntVector (and vice versa) before calling the double_it function.

>>> import my_ext
>>> my_ext.double_it([1, 2, 3])
my_ext.IntVector([2, 4, 6])

my_ext.double_it.__doc__
'double_it(arg: my_ext.IntVector, /) -> my_ext.IntVector'

Good thing about bindings is that they don’t require the costly conversion step when crossing the language boundary. They also support mutable references, so the issue discussed in the context of type casters does not arise. Sometimes, binding is the only available option: when a C++ type does not have an equivalent Python type, casting simply does not make sense.

The problem with bindings is that it is additional work and code that you need to write. There are not many types for which nanobind provides binding functions.
The only ones which are available are for std::vector<>, std::map<>, std::unordered_map<>, iterators and some other types. Most of the time, you will need to write the binding code yourself.