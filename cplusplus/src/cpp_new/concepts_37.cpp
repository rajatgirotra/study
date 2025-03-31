/*
 * in concepts_36.cpp, you have seen requires CLAUSE and how to write a concept.
 * Here we will see how we can re-use the requires keyword to write a requires expression.
 *
 * NOTE: A requires EXPRESSION is also a CONSTRAINT.
 *
 * let say we want the same maxValue() function for pointers. But this time we have smart pointers. not raw pointers.
 * so std::is_pointer_v<T> will be false for smart pointers. Let say we also want to make sure:
 * 1) the pointer type can be compared to null pointer
 * 2) the pointer types can be compared to each other
 * 3) the maxValue() function can work with smart pointers.
 *
 * We can create a concept using a requires EXPRESSION.
 */

#include <iomanip>
#include <type_traits>
#include <iostream>
#include <memory>
using namespace std;

template <typename T>
concept IsPointer = requires (T p) {  // this is a requires EXPRESSION
  // list of requirements.
  *p; // means that the parameter type T can be dereferenced.
    { p < p } -> std::convertible_to<bool>; // comparison should be able to yield bool
    p == nullptr; // p should be comparable to nullptr
};
/* the above concept will not work with iterators in general as they cannot be compared to nullptr */

template <typename T>
auto maxValue(const T& a, const T& b) {
    return a > b ? a : b;
}

template <typename T>
requires IsPointer<T> // template function with requires is also assumed to be more specialized.
auto maxValue(const T& a, const T& b) requires std::three_way_comparable_with<decltype(*a), decltype(*b)> {
    return maxValue(*a, *b);
}

/*
 * a requires CLAUSE and a requires EXPRESSION can also be used together.
 */
template <typename T>
requires requires(T p) { *p; }
decltype(auto) minValue(const T& a, const T& b) {
    return a < b ? a : b;
}

int main() {
    auto px = std::make_unique<int>(20);
    auto py = std::make_unique<int>(10);
    cout << maxValue(px, py) << endl;
    cout << *minValue(px, py) << endl; // wrong answer.
}

