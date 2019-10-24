/* You know that for compilers can deduce the function template arguments from the parameter types of the funtions already. in C++17, compilers can now deduce the type of the template arguments of classes also from the initializer. ie.

std::pair p(10, 2.0) is valid. Earlier you had to type std::pair<int, double> p(10, 2.) or std::make_pair(10, 2.0).

std::less l; // by default, l is void.

What are the rules.

1) deduction is done if no template argument is specified. If partial template arguments are specified, deduction is not done. Eg:
std::tuple t(1, 2, 3); // t is deduced of type std::tuple<int, int, int>
std::tuple<int> t2(1, 2, 3); // t is NOT deduced.

The standard describes how the deduction is done by the following steps. Example,

template <typename T>
struct S {
    template <typename U>
    struct N {
        N(T);
        N(T, U);
        template <typename V>
        N (V, U);
    };
};

S<int>::N x{2.0, 1};

1) For every constructor (plus for the copy c'tor) the compiler generates function templates whose template types are the template types of the class, followed by any template parameters of the template c'tor

2) The parameters of the function templates are the parameters of the ctor
3) The return type of the function templates is the name of the template class with the class template parameters. Out of all these the suitable overload is selected based on actual arguments passed in the initializer. For example, in the case above, we have the following 4 function templates

template <U> S<int>::N<U> FUNC(int);
template <U> S<int>::N<U> FUNC(int, U);
template <U, V> S<int>::N<U> FUNC(V, U);
template <U> S<int>::N<U> FUNC(S<int>::N<U>);

Clearly the initializer {2.0, 1} means the third overload is selected. So V is double and U is int.

Example 2
---------
template <typename T> struct UniquePtr { UniquePtr(T* t) };
So overloads are
template <typename T> UniquePtr<T> FUNC(T* t);
template <typename T> UniquePtr<T> FUNC(UniquePtr<T>);

So, in "UniquePtr dp{new auto(2.0)};", auto is deduced to be of double type from the initializer there overload 1 is matched and T is double.

It turnes out that you can also specify USER DEFINED DEDUCTION GUIDES (means you can specify your own overload resolution preference). The syntax is similar to that of trailing function type syntax:

explicit(optional) template_name(parameters) -> deduced_type.
*/

#include <iostream>
#include <type_traits>
#include <functional>
#include <vector>
#include <string>
using namespace std;

template <typename T> struct S {
    template <typename U> struct N {
        N(T) {};
        N(T, U) {};
        template <typename V> N(V, U) {};
    };
};

template <typename T> struct UniquePtr { UniquePtr(T* t) {}; };

template <typename T> struct container {
    container(T t) {};
    template <typename Iter> container(Iter first, Iter end) {};
};
// user defined deduction guide
template <typename Iter> container(Iter first, Iter end) -> container<typename std::iterator_traits<Iter>::value_type>;

template <typename T> struct X {
    X(T) {};
};
// user defined deduction guide
X(const char*) -> X<std::string>;

int main() {
    cout << std::boolalpha;
    S<int>::N x{2.0, 1};
    cout << std::is_same<decltype(x), S<int>::N<int>>::value << endl; 

    UniquePtr y{new auto(2.0)};
    cout << std::is_same<decltype(y), UniquePtr<double>>::value << endl; 

    container c(7); 
    cout << std::is_same<decltype(c), container<int>>::value << endl; 

    std::vector v{1.0, 2.0, 3.0};
    cout << std::is_same<decltype(v), std::vector<double>>::value << endl; 

    auto d = container(v.begin(), v.end());
    cout << std::is_same<decltype(d), container<double>>::value << endl; 

    X xx{"Hello World"};
    cout << std::is_same<decltype(xx), X<const char*>>::value << endl; 
    cout << std::is_same<decltype(xx), X<std::string>>::value << endl; 

    return 0;
}
