/*
 * Continuing on RVO from 16_README.txt, C++17 guarantees that compiler must elide a copy (ie must do RVO).
 * NRVO is still not mandatory but most compilers do it anyway. What this means is that the compilers defer object materialization.
 */
#include <iostream>
#include <array>
using namespace std;

struct NoCopyMove {
    std::array<int, 1024> m_arr;
    int m_v;

    NoCopyMove(int arg = 0) : m_v(arg) {}

    // delete copy and move ctor
    NoCopyMove(const NoCopyMove&) = delete;
    NoCopyMove(NoCopyMove&&) = delete;
};

NoCopyMove foo(int arg) {
    if(arg > 0)
        return NoCopyMove(arg); // compiler uses RVO
    return NoCopyMove(-arg);
}

//NoCopyMove foo(int arg) {
//    if(arg > 0) {
//        NoCopyMove x(arg); // compiler uses RVO
//        return x;
//    }
//
//    NoCopyMove y(-arg); // compiler uses RVO
//    return y;
//}


int main() {
    NoCopyMove o = foo(-98);
    cout << o.m_v;
}