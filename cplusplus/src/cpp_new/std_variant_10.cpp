/*
 * using std::visit() to modify the variant
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

struct MultiplyVisitor {
    double m_factor;
    MultiplyVisitor(double arg) : m_factor(arg) {}

    void operator() (int& i) {
        i *= i;
    }

    void operator() (double& d) {
        d *= m_factor;
    }

    void operator() (const string&) {
    }
};

int main() {
    // generic PrintVisitor using generic lambda
    auto print_visitor = [](const auto& t) { cout << t << endl; };

    std::variant<int, double, string> var(10);
    MultiplyVisitor mul(0.5);

    // print and mutate int
    cout << "Printing and mutating int\n";
    std::visit(print_visitor, var);
    std::visit(mul, var);
    std::visit(print_visitor, var);

    cout << "Printing and mutating double\n";
    var.emplace<1>(3.2);
    std::visit(print_visitor, var);
    std::visit(mul, var);
    std::visit(print_visitor, var);

    cout << "Printing and mutating string\n";
    var.emplace<2>("HelloWorld");
    std::visit(print_visitor, var);
    std::visit(mul, var);
    std::visit(print_visitor, var);
}

/* So now you have seen there are so many ways to modify variant's alternatives
 * 1. plain assignment
 * 2. emplace<type of index>
 * 3. std::get<> (returns a reference)
 * 4. std::get_if<> (returns a pointer)
 * 5. std::visit() where the function call operator accept parameters by reference
 */