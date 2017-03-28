// Copyright (C) 2015 by RajatGirotra
// We'll show what std::get<> returns from a tuple
#include <iostream>
#include <tuple>
#include <string>
#include <memory>
using std::cout;
using std::unique_ptr;
using std::string;
using std::endl;

struct A {
    explicit A(int&& n) {
        cout << "rvalue ordered: " << n << endl;
    }

    explicit A(int& n) {
        cout << "lvalue ordered: " << n << endl;
    }

    explicit A(const int& n) {
        cout << "const lvalue ordered: " << n << endl;
    }
};

int main(int argc, char *argv[]) {
    int i = 10;
    const int x = 20;
    auto tpl = std::make_tuple(100, i, x);
    A a1(std::get<0>(tpl));
    A ax(std::get<0>(std::make_tuple(100)));
    A ay(std::get<1>(std::make_tuple(100, x)));
    cout << "i: " << i << endl;
    A a2(std::get<1>(tpl));
    A a3(std::get<2>(tpl));
    return 0;
}

