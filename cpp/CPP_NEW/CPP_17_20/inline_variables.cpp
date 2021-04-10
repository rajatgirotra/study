#include "inline_variables.hpp"
#include <iostream>
using std::cout;
using std::endl;


void printStaticValue() {
    cout << X::m_tag << endl;
    cout << X::m_tag_2 << endl;
    cout << X::m_random_value << endl;
}