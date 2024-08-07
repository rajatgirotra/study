// Copyright (C) 2015 by RajatGirotra

// std::tie - Takes as argument lvalue references only.
// and creates a tuple where each type is an lvalue reference to the
// argument passed to the function.
// std::tie(mychar, myint, mybool) will create a tuple
// where first type is an lvalue reference to mychar, second type
// is an lvalue reference to myint and third type is an lvalue reference to
// mybool.
#include <iostream>
#include <tuple>
#include <string>
using std::tuple;
using std::cout;
using std::endl;
using std::tie;

int main(int argc, char *argv[]) {
    tuple<int, char, bool> t1(10, 'a', false);
    int myint = -1;
    char mychar = 127;
    bool mybool = true;
    // A very good way to unpack tuple object.
    std::tie(myint, mychar, mybool) = t1; // tie returns tuple<int&, char&, bool&> where int& points to myint,
                                          // char& points to mychar, bool& points to mybool.
                                          // the assignment operator then assigns myint a value of 10,
                                          // mychar as 'a' and mybool as false
    cout << "int: " << myint << "  char: " << mychar
         << "  bool: " << std::boolalpha << mybool << endl;
    // Also note that the tuple created by tie is updated with t1
    // which updates myint, mychar and mybool and then the tuple
    // gets destroyed immediately.
    return 0;
}

/*
 A note on comparisons. Tuples can be compared using ==, !=, <=, >=, <, >
 comparison compares each type in order and returns true when it find the
 a comparison which returns true.
*/
