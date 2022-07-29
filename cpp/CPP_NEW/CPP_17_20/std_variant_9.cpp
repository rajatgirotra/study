/*
 * std::variant is a type safe union. a std::variant holds one of its alternatives at any given time or no value (in case of error).
 * default constructed variants default to the first alternative, given that the first alternative is default constructable.
 * otherwise, the variant is not default constructable.
 *
 * variant can hold the same type more than once or even hold cv-qualified versions of the same type.
 * variant cannot hold references, arrays or void types.
 *
 * just like std::optional a variant cannot do dynamic memory allocation.
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
    void operator() ([[maybe_unused]] float f) { cout << "float: " << f << endl; }
    void operator() ([[maybe_unused]] const string& s) { cout << "string: " << s << endl; }
};

struct NotSimple {
    NotSimple(int, float) {};
};

struct FirstType {
    FirstType() { cout << "FirstType::FirstType()\n"; }
    ~FirstType() { cout << "FirstType::~FirstType()\n"; }
};

struct SecondType {
    SecondType() { cout << "SecondType::SecondType()\n"; }
    ~SecondType() { cout << "SecondType::~SecondType()\n"; }
    SecondType(const SecondType&) { cout << "SecondType(const SecondType&)\n"; }
    void operator=(const SecondType&) { cout << "void operator=(const SecondType&)\n"; }
    SecondType(SecondType&&)  noexcept { cout << "SecondType(SecondType&&)\n"; }
    void operator=(SecondType&&)  noexcept { cout << "void operator=(SecondType&&)\n"; }
};

int main() {
    std::variant<int, double, string> intDoubleStringVar; // default initialization will make the first alternate active (ie int)
    // print the size of variant, size is the number of alternative, i.e. the number of template arguments
    cout << "size of intDoubleString variant: " << std::variant_size_v<decltype(intDoubleStringVar)> << endl;
    static_assert(variant_size_v<decltype(intDoubleStringVar)> == 3);

    // visiting a variant: the visit() function takes a callable and calls the appropriate callable depending on the active member
    std::visit(VariantVisitor(), intDoubleStringVar);

    // index function (returns a zero based index of the current alternative held by the variant)
    auto x = intDoubleStringVar.index();
    cout << "index when intDoubleStringVar holds an integer: " << x << endl;

    intDoubleStringVar = 5.5;
    x = intDoubleStringVar.index();
    cout << "index when intDoubleStringVar holds a double: " << x << endl;

    intDoubleStringVar = "Hello World";
    x = intDoubleStringVar.index();
    cout << "index when intDoubleStringVar holds a string: " << x << endl;

    /*
     * get_if<> --> Very handy, it returns a pointer (could be nullptr) to the alternative you ask for.
     * If the alternative you ask for is also the current alternative, returns a pointer to that alternative.
     * otherwise, returns nullptr. This is handy as it doesn't throw.
     *
     * The other thing to note is that it takes a pointer to a variant instead of taking a variant simply like a const l-value reference
     * The reason is that a const l-value reference can bind to temporary variants, and returning a pointer to an alternative inside it
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

    /* When your variant first alternative is not default constructable, use std::monostate as the first alternative, which makes your variant
     * default constructable.
     */
    cout << "\nmonostate use.\n";
    std::variant<std::monostate, NotSimple, string> monostateVar;
    cout << "monostateVar index(): " << monostateVar.index() << endl;
    try {
        [[maybe_unused]] auto tmp = std::get<std::monostate>(monostateVar); // gcc defines monostate as struct monostate{};
        // cannot do anything with monostate really, just used to make the variant default constructable.
    } catch(const std::bad_variant_access& e) {
        cout << "exception caught: " << e.what() << endl;
    }

    cout << "\ncreating a variant with any alternative\n";
    std::variant<int, double, string> var1(3.5);
    cout << "variant with double alternative, index: " << var1.index() << ", value: " << std::get<double>(var1) << endl;

    /* yields an error as 3.5 is a double, so it can be narrowed to an int or float both, so compiler cannot decide.
     * use std::in_place_index<> to tell the compiler explicitly
     */
    // std::variant<int, float, string> var2(3.5);
    //std::variant<int, float, string> var2(std::in_place_index<1>, 3.5);
    std::variant<int, float, string> var2(std::in_place_type<float>, 3.5);
    cout << "variant with float alternative, index: " << var2.index() << ", value: " << std::get<float>(var2) << endl;

    /* since initializer is const char*, the variant uses C++ rules of converting constructor to convert const char* to one of the alternatives
     * there are two ways: convert const char* to bool or convert to std::string. since bool is a built-in type, the compiler selects it.
     * But gcc 10.0 onwards this is fixed.
     */
    cout << "\nstrange variant initialization\n";
    std::variant<string, int, bool> var3 = "Hello World";
    if(std::holds_alternative<bool>(var3)) {
        cout << "var3, index: " << var3.index() << ", val: " << *std::get_if<bool>(&var3) << endl;
    } else {
        cout << "var3, index: " << var3.index() << ", val: " << *std::get_if<string>(&var3) << endl;
    }

    variant<float, long, double> var4 = 0; // will be ambiguous till gcc 9, gcc 10 onwards this is fixed and will be long
    cout << "Variant<float, long, double> var4 = 0; active index: " << var4.index() << endl;

    cout << "\n changing variant type or values\n";
    std::variant<int, float, std::string> intFloatString { "Hello" };
    std::visit(VariantVisitor(), intFloatString);
    intFloatString = 10; // change value using plain assignment.
    std::visit(VariantVisitor(), intFloatString);
    intFloatString.emplace<1>(3.6f); // or use emplace<index> function
    std::visit(VariantVisitor(), intFloatString);
    intFloatString.emplace<string>("Hello"); // or use emplace<type> function
    std::visit(VariantVisitor(), intFloatString);
    std::get<string>(intFloatString) += " World"; // std::get<> returns a reference, so we can change the value straight away.
    std::visit(VariantVisitor(), intFloatString);
    intFloatString = 10.5f;
    std::visit(VariantVisitor(), intFloatString);
    auto floatPtr = std::get_if<float>(&intFloatString);
    assert(floatPtr != nullptr);
    *floatPtr += 5;
    std::visit(VariantVisitor(), intFloatString);

    // note that the variant is responsible for calling the dtor of the underlying type when you change its type. so there is no memory leak.
    // let's see a trivial example:
    {
        std::variant<FirstType, SecondType> var5;
        {
//            var5 = SecondType();
              var5.emplace<SecondType>(SecondType()); // both this and the line above give same outputs.
        }
        cout << "var5 holds SecondType() which will be destroyed at the end of this scope.\n";
    }
}
