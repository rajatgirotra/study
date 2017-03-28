// Copyright (C) 2015 by RajatGirotra

// Generate assembly code and check is unsigned division for
// integers is faster than signed division where divisor is a
// constant and a power of 2.
#include <iostream>
using std::cout;
using std::endl;

// Keep divisor signed instead of unsigned
// because if numerator is signed (and -ive) and divisor is unsigned
// result will be converted to unsigned.
static const int divisor = 8;

int signed_divison(int x) {
    return x / divisor;
}

unsigned int  unsigned_divison(unsigned int x) {
    return x / divisor;
}

int main() {
    int x = -10;
    unsigned int y = 10;
    x = signed_divison(x);
    y = unsigned_divison(y);
    cout << x << " " << y << endl;
    return 0;
}
