#include "5.hpp"
#include <iostream>
using namespace std;

int main() {
    unsigned const one = binary<1>::value;
    unsigned const three = binary<11>::value;
    unsigned const five = binary<101>::value;
    unsigned const seven = binary<111>::value;
    unsigned const nine = binary<1001>::value;

    cout << one << endl << three << endl << five << endl << seven << endl << nine << endl;

    return 0;
};
