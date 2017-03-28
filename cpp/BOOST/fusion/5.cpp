// Copyright (C) 2015 by RajatGirotra
/*
The next beautiful concept is the map associative sequence.
Generally a map stores key value pairs(in the form of std::pair).
In Fusion too, map stores key values, but of type boost::fusion::pair
The great though is that the key does not have any value. It is just a type.
Only the second template parameter has a value which you can access using pair.second

Just like a map has unique keys, a fusion map will have unique keys, so if 
map<pair<int, char>, pair<int, double>> is wrong.

But what is all this useful for??
maps in fusion are a great alternative to structures. How? Lets see. A structure
has members, where each member has a type and value. Similary, you can define
a map in fusion.
*/

#include <boost/fusion/sequence.hpp>
#include <boost/fusion/container.hpp>
#include <iostream>
#include <string>

using boost::fusion::map;
using boost::fusion::pair;
using boost::fusion::make_pair;
using boost::fusion::at_key;
using std::cout;
using std::endl;
using std::string;

namespace fields {
    // declare some types
    struct name;
    /* name is a type now. It does not matter that its not
       defined. We can still use it as a key
    */
    struct age;
}

int main(int argc, char *argv[]) {
    typedef map<pair<fields::name, string>, pair<fields::age, int>> person_t;
    person_t person(make_pair<fields::name>("Rajat"), make_pair<fields::age>(32));

    cout << at_key<fields::name>(person) << endl;
    cout << at_key<fields::age>(person) << endl;
    return 0;
}

/*
Advantage of using fusion maps over struct is that you get to use whole bunch of
generic algorithms defined in fusion
*/
