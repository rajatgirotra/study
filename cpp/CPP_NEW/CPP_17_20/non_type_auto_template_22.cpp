/*
 * cpp 17 allows another re-use of the keyword auto. You can re-use it for specifying it as a non-template parameter type.
 */

#include <iostream>
#include <type_traits>
#include <cxxabi.h>
#include <string>
#include <cassert>
#include <typeinfo>
using namespace std;

string demangle(const char* mangled_name) {
    int result {};
    auto res = abi::__cxa_demangle(mangled_name, nullptr, nullptr, &result);
    assert(result >= 0);
    string res_str(res);
    free(res);
    return res_str;
}

template <auto N>
// template <size_t N>
void f() {
    cout << "f with N: " << N << endl;
}
// the above is not a great example as you could always use size_t. You don't need to use typename T anyway.

// another example
template <typename T, T value>
constexpr T my_constant = value; // my_constant is a variable template as you saw in variable_template_6.cpp and variable_template_7.cpp
constexpr auto my_int_const = my_constant<int, 100>;

// new way for above using auto
template <auto N>
constexpr auto my_constant_new_way = N;
constexpr auto my_int_const_new_way = my_constant_new_way<100>;

//creating a heterogeneous list at compile time
template <auto... Args>
struct HeterogeneousValueList {};

int main() {
    f<10>();
    cout << demangle(typeid(my_int_const).name()) << endl;
    cout << demangle(typeid(my_int_const_new_way).name()) << endl;

    static_assert(std::is_same_v<decltype(my_int_const), const int>);

    [[maybe_unused]] constexpr HeterogeneousValueList<'a', 100, true> obj;
}
