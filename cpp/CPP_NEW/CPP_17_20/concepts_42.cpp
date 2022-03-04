/*
 * CONSTRAINTS can be:
 * 1) an ad-hoc compile time boolean expression
 * 2) a requires expression
 * 3) a concept.
 *
 * CONSTRAINTS can be joined together using && or ||
 *
 * Read Section 3.3 Contraints in details of C++20 book on some cool ways to specify contraints.
 */

#include <iostream>
#include <type_traits>
#include <concepts>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

template <typename T>
requires (sizeof(T) > 4
          && requires { typename T::value_type; }
          && std::input_iterator<T>
          )
void foo(const T& val) {}

/*
 * Also, you know we can use concepts at multiple places as Type constraints. Let's see it in action.
 */

template <typename T>
concept DummyConcept = std::is_pointer_v<T>;

// using concept as type constraint
template <DummyConcept T>
void bar(T val) {}

auto func(const DummyConcept auto& arg) {}

template <typename T>
requires requires (T val) {
    { val + val } -> DummyConcept;
}
void some_func() {}

// But this is a simple concept involving only one template parameter. What if you have a concept involving multiple paramaters?
// how do you use it in a type constraint?? Let's see.
// std::convertible_to<FROM, TO> is a std concept involving two template parameters. WE can se such contraints which involve multiple
// parameters as type constraints, and the parameter type or the return value is then used as the first argument. See below what it means.

template <std::convertible_to<int> T> // the template parameter T is used as the first argument to std::convertible_to.
class MyClass {};

auto myFunc(const std::convertible_to<int> auto& val) {} // equivalent to std::convertible_to<decltype(val), int>

template <typename T>
requires requires (T val) {
    { val + val } -> std::convertible_to<int>; // means return type of {val+val} should be convertible to int
}
void some_func() {}

// another useful concept introduced is std::invocable. see its use.
template <std::invocable<int, std::string> Callable>
void call(Callable op) {} // guarantees that op(5, string("Hello")) is callable.

auto some_op(std::integral auto val) {
    return val;
}

// Just remember that type constraints can be used at any place where "auto" can be used. See examples below
std::integral auto val1 = 42;
//std::integral auto val2 = 100.; // error

std::integral auto foobar() {}

template <typename T, std::integral auto max>
class SizedColl {};

template <typename T, std::convertible_to<T> auto N>
class MyType {};

int main() {
//    some_op(3.5); // not allowed for floating points
   SizedColl<string, 5> sc;
//   MyType<string, std::index_sequence<1>> mt;
}
