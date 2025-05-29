/*
 * template <typename Callable, typename... Variants>
 * std::visit(Callable, Variants&&... vars)
 *
 * If you see visit can take multiple variants, in this case it needs to provide a visit Callable that provides a cross product
 * combination of all arguments from the two lambdas. Example:
 *
 * variant<int, double> var1;
 * variant<string, X> var2;
 *
 * visit callable should provide 4 overloads for (int, string), (int, X), (double, string), (double, X)
 * We can exploit this to get an interesting pattern. Let's say we only want the combination (double, string) to be valid.
 * Then we can implement that explicitly and others using generic lambda.
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

struct X{};


int main() {
    // generic PrintVisitor using generic lambda
    std::variant<int, double> var1;
    std::variant<string, X> var2;

    // print
    std::visit(overload {
        [](const double&, const string&) { cout << "double and string combination is valid!! " << endl; },
        [](const auto& arg1, const auto& arg2) { cout << demangle(typeid(arg1).name()) << " and " << demangle(typeid(arg2).name()) << " combination is not valid!!" << endl; }
        }, var1, var2);

    var1.emplace<double>(5.5);

    // print again
    std::visit(overload {
            [](const double&, const string&) { cout << "double and string combination is valid!! " << endl; },
            [](const auto& arg1, const auto& arg2) { cout << demangle(typeid(arg1).name()) << " and " << demangle(typeid(arg2).name()) << " combination is not valid!!" << endl; }
    }, var1, var2);

}
