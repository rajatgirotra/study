/*
 * variables templates in C++ (it's available in C++14 onwards)
 */

#include <iostream>
#include <cstdint>
#include <iomanip>
#include <type_traits>
#include <cxxabi.h>
#include <string>
#include <cassert>
#include <typeinfo>
#include <boost/type_index.hpp>
using namespace std;

namespace {
    string demangle(const char* mangled_name) {
        int res{};
        auto demangled_name = abi::__cxa_demangle(mangled_name, nullptr, nullptr, &res);
        assert(res == 0);
        string result(demangled_name);
        free(demangled_name);
        return result;
    }
}

// it's a template to return the value of pi as a particular type you require.
//template <typename T>
//constexpr T pi = T{3.1415926538979323L};

template <typename T>
constexpr T pi = T(3.1415926538979323L);

int main() {
    using boost::typeindex::type_id_with_cvr;
    std::cout << pi<float> << endl; // print pi as a float
    std::cout << std::setprecision(20) << pi<double> << endl; // print pi as a double
    std::cout << std::setprecision(20) << pi<long double> << endl; // print pi as a double
    cout << "decltype(pi<double>): " << std::is_same<decltype(pi<double>), double>::value << endl; // this will be false as pi<double> is const double
    cout << "decltype(pi<double>): " << demangle(typeid(pi<double>).name()) << endl; // C++ typeinfo only reports double.
    cout << "decltype(pi<double>): " << type_id_with_cvr<decltype(pi<double>)>().pretty_name() << endl; // but boost typeindex is designed to succeed.

    // what is wrong here.
    // pi<int32_t> means "int pi = int {3.1415926538979323L}; i.e. you are using brace initialization with narrowing cast. try substituting it with parenthesized substitution.
    std::cout << pi<int32_t> << endl; // print pi as a signed 32 bit int
}

/*
 * That doesn't sound very interesting. What's the point? see variables_template_7.cpp
 */
