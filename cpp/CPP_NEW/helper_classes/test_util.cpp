#include "CStrLen.hpp"
#include "CSVar.hpp"
#include <iostream>

using namespace std;
using namespace util;

int main() {
//    const char* s = "HelloG";
//    CStrLen o(s, 1);
//    CStrLen o2(s, 10);
//    cout << o << endl;
//
//    string str {"Cruel World"};
//    CStrLen o3(str);
//    cout << o3 << endl;
//
//    auto x = CSLO("Hello Macro");
//    cout << x << endl;

    [[maybe_unused]] short s = 10;
    [[maybe_unused]] unsigned short us = 10;
    [[maybe_unused]] int i = 10;
    [[maybe_unused]] unsigned int ui = 10;
    [[maybe_unused]] long l = 10;
    [[maybe_unused]] unsigned ul = 10;
    [[maybe_unused]] std::int32_t int32 = 10;
    [[maybe_unused]] std::int32_t uint32 = 10;
    [[maybe_unused]] std::int64_t int64 = 10;
    [[maybe_unused]] std::int64_t uint64 = 10;
    [[maybe_unused]] bool b = true;
    CSVar var1(b);
    cout << var1.getType() << endl;
}