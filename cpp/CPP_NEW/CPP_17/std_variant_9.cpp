/*
 * std::variant is a type safe union. let's see it in action
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

struct VariantVisitor {
    void operator() ([[maybe_unused]] int i) { cout << "int: " << i << endl; }
    void operator() ([[maybe_unused]] double d) { cout << "double: " << d << endl; }
    void operator() ([[maybe_unused]] const string& s) { cout << "string: " << s << endl; }
};

int main() {
    std::variant<int, double, string> intDoubleStringVar; // default initialization will make the first alternate active (ie int)
    // print the size of variant
    cout << "size of intDoubleString variant: " << std::variant_size_v<decltype(intDoubleStringVar)> << endl;
    static_assert(variant_size_v<decltype(intDoubleStringVar)> == 3);

    // visiting a variant: the visit() function takes a callable and calls the appropriate callable depending on the active member
    // if i comment out the operator() overload taking an integer, the operator() taking a double is called. Need to check the behavior here.
    std::visit(VariantVisitor(), intDoubleStringVar);

    // index function (returns a zero based index of the current alternative held by the variant)
    auto x = intDoubleStringVar.index();
    cout << "index when intDoubleStringVar holds an integer: " << x << endl;

    intDoubleStringVar = 5.5;
    x = intDoubleStringVar.index();
    cout << "index when intDoubleStringVar holds an double: " << x << endl;

    intDoubleStringVar = "Hello World";
    x = intDoubleStringVar.index();
    cout << "index when intDoubleStringVar holds an string: " << x << endl;

    /*
     * get_if<> --> Very handy, it returns a pointer (could be nullptr) to the alternative you ask for.
     * If the alternative you ask for is also the current alternative, returns a pointer to that alternative.
     * otherwise returns nullptr. This is handy as it doesnt throw.
     *
     * The other thing to note is that it takes a pointer to a variant instead of taking a variant simple like a const l-value reference
     * The reason is that it a const l-value reference can bind to temporary variants, and returning a pointer to an alternative inside it
     * would result in a crash. We should have done the same thing for SDict class in DB.
     */
    if (const auto isCurrentIndexInt = std::get_if<int>(&intDoubleStringVar)) {
        cout << "int index is active, value: " << *isCurrentIndexInt << endl;
    } else if (const auto isCurrentIndexDouble = std::get_if<double>(&intDoubleStringVar)) {
        cout << "double index is active, value: " << *isCurrentIndexDouble << endl;
    } else if (const auto isCurrentIndexString = std::get_if<string>(&intDoubleStringVar)) {
        cout << "string index is active, value: " << *isCurrentIndexString << endl;
    }
    // get_if<> can take either a type T (as shown) or an index (std::size_t). Note that the version taking a type only works if the variant holds that type
    // only once.

    // holds_alternative<> returns a boolean. it only takes a type and not index. the variant should hold the type only once.
    if (std::holds_alternative<int>(intDoubleStringVar)) {
        cout << "variant holds integer\n";
    } else if (std::holds_alternative<double>(intDoubleStringVar)) {
        cout << "variant holds double\n";
    } else if (std::holds_alternative<string>(intDoubleStringVar)) {
        cout << "variant holds string\n";
    }

    // try to access alternative which isn't set at the moment. variant protects you from accessing non-current alternatives.
    try {
        std::get<double>(intDoubleStringVar);
    } catch(const std::bad_variant_access& e) {
        cout << "exception caught: " << e.what() << endl;
    }
}