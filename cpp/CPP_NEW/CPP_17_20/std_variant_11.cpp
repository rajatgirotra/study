/*
 * C++20 proposes to add an overload function that allows you to specify all overloads of the visitor in class right at
 * the place you call std::visit. We can do that at the moment using C++17 template argument deduction guides.
 * Lets see
 */

#include <iostream>
#include <string>
#include <variant>
#include <cxxabi.h>
#include <cassert>
#include <typeinfo>

using namespace std;
namespace {
    [[maybe_unused]] string demangle(const char* mangled_name) {
        int result {-1};
        auto demangled_name = abi::__cxa_demangle(mangled_name, nullptr, nullptr, &result);
        assert(result == 0);
        string name(demangled_name);
        free(demangled_name);
        return name;
    }
}

template <typename... Lambdas>
struct overload : Lambdas... {
    using Lambdas::operator()... ;
};

template <typename... Lambdas> overload(Lambdas...) -> overload<Lambdas...>;


int main() {
    // generic PrintVisitor using generic lambda
    std::variant<int, double, string> var(10);

    // print and mutate int
    cout << "Printing and mutating int\n";
    std::visit(overload {
        [](const int& i) { cout << "integer: " << i << endl; },
        [](const double& d) { cout << "double: " << d << endl; },
        [](const string& s) { cout << "string: " << s << endl; }
        }, var);

    std::visit(overload {
            [](int& i) { i *= i; },
            [](double& d) { d *= 0.5; },
            [](const string& ) {  }
    }, var);

    std::visit(overload {
            [](const int& i) { cout << "integer: " << i << endl; },
            [](const double& d) { cout << "double: " << d << endl; },
            [](const string& s) { cout << "string: " << s << endl; }
    }, var);
}