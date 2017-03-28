#include <iostream>
#include <functional>
using namespace std;

// read test.cpp first
int main() {
    int a {10}, b {20};

    std::reference_wrapper<int> wrap1(a);
    std::reference_wrapper<int> wrap2(b);

    wrap1 = wrap2;  // wrap1 and wrap2 now both are references to b.
    ++wrap1; ++wrap2; // read test.cpp to see how this is made possible.
    cout << "Wrap1: " << wrap1 << endl;
    cout << "Wrap2: " << wrap2 << endl;

    a = 10;
    b = 20;
    int& x = a;
    int& y = b;
    x = y; // x still references a, and y still references b
    x++; y++;
    cout << "x: " << x << endl;
    cout << "y: " << y << endl;

    wrap1.get() = 50;  // get() returns T&
    cout << "Wrap1: " << wrap1 << endl;
    cout << "Wrap2: " << wrap2 << endl;

    return 0;
}
