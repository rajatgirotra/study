/*
template <typename... Types>
std::tuple<Types&&...> forward_as_tuple(Types&&... types)

forward_as_tuple() returns a tuple of references. References can be either lvalue reference or rvalue reference depending on if the argument is lvalue or rvalue. Please note that if argument is rvalue, then forward_as_tuple() is not going to extend their lifetime. So forward_as_tuple() is mainly used in an expression.
*/

#include <tuple>
#include <iostream>
#include <string>
#include <functional>
#include <map>
using namespace std;

int main() {
    map<int, string> m;

    m.emplace(std::piecewise_construct,
              std::forward_as_tuple(10), // will return tuple<int&&> which will be passed to int c'tor
              std::forward_as_tuple(20, 'a') // will return tuple<char&&, int&&> which will be passed to string c'tor
             );

    cout << m[10] << endl;

    auto t = std::forward_as_tuple(20, 'b'); // t will be of type tuple<char&&, int&&>
    //m.emplace(std::piecewise_construct, std::forward_as_tuple(50), t); // ERROR. t is holding dangling references.
    return 0;
}

