/*
 * You already know a generic lambda (whose parameters are auto) is a template under the hood.
 * auto cmp = [] (const auto& x, const auto& y) {
 *   return x > y;
 * };
 *
 * is same as:
* class NameChosenByCompiler {
*   public:
*     template<typename T1, T2>
*     auto operator() (const T1& x, const T2& y) const {
*       return x > y;
*     }
* };
*
* with c++20, the standard allows you to specify a type T explicitly which can be used inside your lambda definition.
* You could have just used decltype(arg) where arg is an "auto" argument type, but using the type T directly is more convenient
*
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

auto foo = []<typename T>(const T &param) {
    cout << "foo called with value: " << param << " of type: " << demangle(typeid(T).name()) << endl;
};

auto arrSize = []<typename T, size_t N>(T (&)[N]) { return N; };

// you could have just written function templates, but lambdas provide the added benefit of capturing scope and be able to be defined inside
// other function.

// A generic lambda and a specialization for it that uses a template parameter
auto genericVisitor = [](auto &&arg) {
    if constexpr (std::is_same_v<std::decay_t<decltype(arg)>, std::string>) {
        cout << "visitor for string, arg: " << arg << endl;
    } else {
        cout << "visitor for " << demangle(typeid(decltype(arg)).name()) << ", arg: " << arg << endl;
    }
};

auto specialVisitor = []<typename T>(T &&arg) {
    if constexpr (std::is_same_v<std::decay_t<T>, std::string>) {
        cout << "visitor for string, arg: " << arg << endl;
    } else {
        cout << "visitor for " << demangle(typeid(T).name()) << ", arg: " << arg << endl;
    }
};

auto lessThan = [](const int &a, const int &b) { return a < b; };
auto lessThanPtr = []<typename T>(const T &a, const T &b) requires std::is_pointer_v<T> { return lessThan(*a, *b); };

// write a function to find first N prime Numbers
template <int Num>
void getPrimes(std::array<int, Num>& res) requires (Num > 0) {
    if (Num >= 1) { res[0] = 2; }
    if (Num >= 2) { res[1] = 3; }
    int idx = 2;

    for (int num = 5; idx < Num; num += 2) { // Skip even numbers after 2
        bool isPrime = true;
        for (int i = 0; i < idx && res[i] * res[i] <= num; ++i) {
            if (num % res[i] == 0) {
                isPrime = false;
                break;
            }
        }
        if (isPrime) {
            res[idx++] = num;
        }
    }
}

// create a lambda which accepts an integer "Num" and returns the first Num prime numbers.
auto primes = []<int Num> requires (Num > 0)() {
    std::array<int, Num> res;
    getPrimes<Num>(res);
    return res;
};

template <int Num>
auto primes2 = [] () {
    std::array<int, Num> res;
    getPrimes<Num>(res);
    return res;
};

int main() {
    foo(10);
    foo("Hello world!");
    foo(25.5);

    [[maybe_unused]] int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    cout << "size of arr[]: " << arrSize(arr) << endl;

    std::variant<int, double, string> var;

    var = 10;
    std::visit(genericVisitor, var);
    std::visit(specialVisitor, var);
    var = 78.6;
    std::visit(genericVisitor, var);
    std::visit(specialVisitor, var);
    var = string("Hello world!");
    std::visit(genericVisitor, var);
    std::visit(specialVisitor, var);

    int a = 2, b = 3;
    cout << std::boolalpha << "lessThan(2, 3): " << lessThan(a, b) << endl;
    cout << std::boolalpha << "lessThan(3, 2): " << lessThan(b, a) << endl;

    int *p1 = &a, *p2 = &b;
    cout << std::boolalpha << "lessThanPtr(2, 3): " << lessThanPtr(p1, p2) << endl;
    cout << std::boolalpha << "lessThanPtr(3, 2): " << lessThanPtr(p2, p1) << endl;

    // clumpsy syntax. Because the syntax is clumpsy, you could make it a variable template. given that your lambda is at file scope.
    // and doesn't capture any scope.
    rng::copy(primes.operator()<10>(), ostream_iterator<int>(cout, " "));
    cout << endl;
    // better syntax
    rng::copy(primes2<10>(), ostream_iterator<int>(cout, " "));
}
