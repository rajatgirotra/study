// Copyright (C) 2015 by RajatGirotra
/*
pair class and its functions - You already know what it is.
Lets see some more usage
*/

#include <boost/fusion/support/pair.hpp>
#include <boost/fusion/include/pair.hpp>
#include <iostream>
#include <string>
#include <typeinfo>
using boost::fusion::pair;
using boost::fusion::make_pair;
using std::endl;
using std::cout;
using std::string;

int main(int argc, char *argv[]) {
    // make a pair
    typedef pair<int, string> pair_t;
    pair_t p1("Hello");
    pair<double, char> p2('X');
    //pair copy c'tor
    pair<int, string> p3 = make_pair<int>("World");

    cout << "p1: " << p1 << "  p2: " << p2 << "  p3: " << p3 << endl;
    cout << "p1: " << p1.second << endl;
    cout << "p1 first_type: " << typeid(pair_t::first_type).name()
         << "  second_type: " << typeid(pair_t::second_type).name() << endl;
    // Can only compare pair's with the same key type.
    // If not wont even compile.
    cout << std::boolalpha << "p1 == p3: " << (p1 == p3) << endl;
    return 0;
}

/*
Refer this link to see fusion::pair reference.
http://www.boost.org/doc/libs/1_60_0/libs/fusion/doc/html/fusion/support/pair.html
Very straight foreward like
pair::first_type
pair::second_type
pair.second
Default c'tor
Copy C'tor
make_pair<First_type>(value)
*/

