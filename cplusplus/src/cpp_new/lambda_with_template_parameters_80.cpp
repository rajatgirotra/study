/*
C++20 now allows you to use lambda init captures with parameter packs, structured bindings.
Also note that implicit capture of *this which was allowed until C++17 is now deprecated.
Let's see all this in action.
*/

#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <type_traits>
#include <concepts>
#include <random>
#include <ranges>
#include <cxxabi.h>
#include <unordered_map>
#include <variant>
using namespace std;
namespace rng = std::ranges;
namespace vws = std::views;

string demangle(const char *mangled_name) {
    int _{};
    auto demangled_name = abi::__cxa_demangle(mangled_name, nullptr, nullptr, &_);
    string result(demangled_name);
    free(demangled_name);
    return result;
}

class Name;
void bar(int value, const Name& n);

class Name {
    private:
    string m_name;

    public:
    Name(string name) : m_name(name) {}

    friend ostream& operator<<(ostream& os, const Name& name) {
        os << name.m_name;
        return os;
    }

    void foo() {
        int val = 10;

        [&] () { bar(val, m_name); }(); // val by ref, m_name by ref, (although C++20 deprecates capture of *this)
        // [val, m_name] { bar(val, m_name); }(); // m_name cannot be captured like that since its storage is not static storage.
        [val, m_name=m_name] { bar(val, m_name); }(); // val and m_name by value
        [&, this] { bar(val, m_name); } (); // val and this by ref. Careful, lambda may outlive "this"
        [&, *this] { bar(val, m_name); }(); // val by ref, m_name by val. Remember, *this creates a copy.
        // [=] { bar(val, m_name); }(); // val by value, m_name by ref (although C++20 deprecates capture of *this)
    }
};

void argPrinter(string str, double d, int v, bool b) {
    // void argPrinter(const string& str, double d, int v, bool b) {
    cout << "argPrinter: " << str << " " << d  << " " << v << " " << b <<endl;
}


template <typename Callable, typename... Args>
auto wrapper(Callable op, Args&&... args) {
    // return a lambda which cout << "Hello" before calling the callable with the arguments
#if 0
    auto result = [op, args...] () mutable { // capturing using "args..." is same as capturing by value
        cout << "Hello\n";
        op(args...);
    };
    return result;
#endif

#if 0
    auto result = [op, &args...] () { // capturing using "&args..." is same as capturing by reference
        cout << "Hello\n";
        op(args...);
    };
    return result;
#endif

#if 0
    auto result = [op, ...args = std::forward<decltype(args)>(args)] () mutable { // using std::move() or std::forward()
        cout << "Hello\n";
        op(args...);
    };
    return result;
#endif

#if 0
    // it is very common to pack variadic arguments inside a tuple and calling std::apply().
    auto result = [op, t = std::make_tuple(std::forward<Args>(args)...)] () mutable { // using std::move() or std::forward()
        cout << "Hello\n";
        std::apply(op, t);
    };
    return result;
#endif

#if 0
    // using std::move(args) and renaming the parameter too fooArgs
    auto result = [op, ...fooArgs = std::move(args)] () mutable { // using std::move() or std::forward()
        cout << "Hello\n";
        std::apply(op, std::make_tuple(std::forward<Args>(fooArgs)...));
    };
    return result;
#endif

#if 1
    // just pass my reference
    auto result = [op, &...fooArgs = args] () mutable { // using std::move() or std::forward()
        cout << "Hello\n";
        op(fooArgs...); // this may crash as arguments are captured by reference and this lambda outlives the arguments.
    };
    return result;
#endif

}

void bar(int value, const Name& n) {
    cout << "Value: " << value << ", Name: " << n << endl;
}

int main() {
    Name name("Rajat");
    name.foo();

    auto f = wrapper(argPrinter, string("HelloWorld"), 28.7, -99, true);
    f();
}