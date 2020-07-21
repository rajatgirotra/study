#include "CStrLen.hpp"
#include <iostream>

using namespace std;
using namespace util;

int main() {
    const char* s = "HelloG";
    CStrLen o(s, 1);
    CStrLen o2(s, 10);
    cout << o << endl;

    string str {"Cruel World"};
    CStrLen o3(str);
    cout << o3 << endl;

    auto x = CSLO("Hello Macro");
    cout << x << endl;
}