// Copyright (C) 2015 by RajatGirotra

/*
fusion for_each(sequence, callable) algo - Its just a generic algo, taking a fusion sequence and
a function object. The function object is called for each element in the sequence.

We use for_each below to print the values in xml
*/
#include <boost/fusion/algorithm.hpp>
#include <boost/fusion/container.hpp>
#include <iostream>
#include <string>
#include <typeinfo>

using std::cout;
using std::endl;
using std::string;

struct print_xml {
    template <typename T>
    void operator() (const T& value) const {
        cout << "<" << typeid(value).name() << ">"
             << value
             << "</" << typeid(value).name() << ">" << endl;
    }
};

int main(int argc, char *argv[]) {
    boost::fusion::vector<int, char, string> data(1, 'x', "Howdy!");
    boost::fusion::for_each(data, print_xml());
    return 0;
}
