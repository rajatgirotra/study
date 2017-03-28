// Copyright (C) 2015 by RajatGirotra

/*
boost::fusion::vector - Is very simple to std::tuple.
instead of using std::get<> use boost::fusion::at_c<>

But it offers much more as we will see
*/
#include <boost/fusion/sequence.hpp>
#include <boost/fusion/container.hpp>
#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

int main(int argc, char *argv[]) {
    boost::fusion::vector<int, char, string> data(1, 'x', "Howdy!");
    auto i = boost::fusion::at_c<0>(data);
    auto s = boost::fusion::at_c<2>(data);
    cout << i << "  " << s << endl;
    return 0;
}
