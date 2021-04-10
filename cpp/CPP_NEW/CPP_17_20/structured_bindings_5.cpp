/*
 * structured bindings allow you to un-pack elements in
 * 1) an array
 * 2) a POD type (like simple structures)
 * 3) a std::tuple like data structure
 */

#include <iostream>
#include <vector>
#include <array>
#include <utility>
#include <tuple>

using namespace std;

struct A {
    int a = 100;
    int b = 200;
};

static A obj;

A& foo() {
    return obj;
}

//A foo() {
//    return obj;
//}

auto bar() {
    return 42;
}

template <typename T>
struct Check;

int main()
{
    // using structured bindings with array. Note that number of VARIABLES UN-PACKED MUST BE SAME AS SIZE OF THE ARRAY
    int arr[] {100, 200};
    auto& [x, y] = arr;
    ++x; --y;
    cout << "arr[0]: " << arr[0] <<", arr[1]: " << arr[1] << endl;

//    auto& [A_a, A_b] = foo(); // foo() returns a temporary so cannot bind to NON-CONST lvalue reference
    auto [A_a, A_b] = foo(); // Note that number of VARIABLES UN-PACKED MUST BE SAME AS NUMBER OF MEMBERS IN THE POD TYPE.
    cout << "A::a: " << A_a << ", A::b: " << A_b << endl;

    /* Very important note, the way structured binding is implemented is that the compiler creates a secret variable under the hood
     * so for this expression it would do something like
     * const auto& a_secret_variable = foo(); and then
     * l = a_secret_variable.a and m = a_secret_variable.b
     * so in this case decltype(a_secret_variable) = const int&, and
     * decltype(l) and decltype(m) = const int ie decltype(a_secret_variable.a) and decltype(a_secret_variable.b)
     *
     * This is just for your information. If foo() returns by lvalue (i.e it returns a temporary, then of course l and obj.a are different.
     * If foo() returns a reference, then of course l and obj.a are same.
     */
    const auto& [l, m] = foo();
    ++obj.a;
    cout << "l: " << l << ", obj.a: " << obj.a << endl;
    [[maybe_unused]] Check<decltype(l)> check_l;

    [[maybe_unused]] const int& i = bar();
    [[maybe_unused]] Check<decltype(i)> check_i;
}