// Copyright (C) 2015 by RajatGirotra

#include <iostream>
#include <string>
#include <tuple>
#include <utility>
#include <typeinfo>
#include "./43.h"
using std::cout;
using std::endl;
using std::tuple;
using std::tuple_size;
using std::tuple_element;

int main() {
    double&& d = std::get<1>(std::make_tuple(100, 23.25));
    // is this ok?? Will d not be a dangling reference?

    auto t1 = std::make_tuple(100, 23.25);
    double&& d2 = std::get<1>(t1);

    cout << d << endl;
    return 0;
}
