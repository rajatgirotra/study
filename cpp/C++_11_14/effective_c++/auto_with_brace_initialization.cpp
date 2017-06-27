/*
gcc 5.1 and up have already fixed the brace initialization with auto problem.
Earlier

auto x = {27};
auto x{27}; were both deduced to be of type std::initializer_list in both C++11 and C++14. They fixed it in C++17 to be of type int instead. But the change was back ported to C++11 and C++14 too and compiler gcc 5.1 and up deduce it to be of type int. 

Some examples are shown below.
*/

#include <iostream>
#include <typeinfo>
using namespace std;

int main() {
auto x1 = { 1, 2 }; // decltype(x1) is std::initializer_list<int>
auto x2 = { 1, 2.0 }; // error: cannot deduce element type
auto x3{ 1, 2 }; // error: not a single element
auto x4 = { 3 }; // decltype(x4) is std::initializer_list<int>
auto x5{ 3 }; // decltype(x5) is int. 

return 0;
}
