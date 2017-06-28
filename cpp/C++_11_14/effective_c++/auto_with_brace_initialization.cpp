/*
gcc 5.1 and up have already fixed the brace initialization with auto problem.
Earlier

auto x = {27};
auto x{27};

were both deduced to be of type std::initializer_list in both C++11 and C++14. They fixed it in C++17  and the second example will be of type int instead. The first remains an std::initializer_list. But the change was back ported to C++11 and C++14 too and compiler gcc 5.1 and up deduce it to be of type int. read (draft N3922) of C++. 

Some examples are shown below. which should show the same output for all -std=c++11/14/17
*/

#include <iostream>
#include <typeinfo>
using namespace std;

int main() {
auto x1 = { 1, 2 }; // decltype(x1) is std::initializer_list<int>
//auto x2 = { 1, 2.0 }; // error: cannot deduce element type
//auto x3{ 1, 2 }; // error: not a single element
auto x4 = { 3 }; // decltype(x4) is std::initializer_list<int>
auto x5{ 3 }; // decltype(x5) is int. 

cout << typeid(decltype(x1)).name() << endl;
cout << typeid(decltype(x4)).name() << endl;
cout << typeid(decltype(x5)).name() << endl;

return 0;
}
