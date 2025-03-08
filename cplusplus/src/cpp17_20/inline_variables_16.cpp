#include "inline_variables.hpp"
#include <iostream>
using namespace  std;
extern void printStaticValue();

int main() {
    printStaticValue();
    cout << "X::m_random_value in main: " << X::m_random_value << endl;
}