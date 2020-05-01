#include <iostream>
using std::cout;
using std::endl;

int main() {
    // by default, lambda's return void
    auto l = []{ cout << "Hello World" << endl; return 0;};
    cout << l() << endl;

    // passing args by value
    int x = 10, y = 20;
    [](int a, int b) { cout << "a: " << a << "   b:" << b << endl; }(x, y);

    // pass by reference.
    [](int& a, int& b) {
        cout << "a: " << a << "   b:" << b << endl;
        a++; --b;
    } (x, y);

    cout << "A, x in main: " << x << endl;
    cout << "A, y in main: " << y << endl;

    // passing scope as read only
    [=] { cout << "x: " << x << "   y:" << y << endl;
        // x++; // cannot increment
    } ();

    // passing scope as read-write
    [&] { cout << "x: " << x << "   y:" << y << endl;
        x--; y++;
    } ();

    cout << "B, x in main: " << x << endl;
    cout << "B, y in main: " << y << endl;

    // passing scope as read-only but mutable, must pass empty argument list
    // if using mutable
    // mutable gives a local copy of every thing in the scope and the lambda can
    // called again with the same values in tact. It does not affect anything outside
    auto d = [=] () mutable { cout << "x: " << x << "   y:" << y << endl;
        x++;
    };
    d();
    cout << "C, x in main: " << x << endl;
    cout << "C, y in main: " << y << endl;
    d();

    x = 10;
    y= 20;

    // passing scope as read-write and mutable, must pass empty argument list
    // if using mutable
    // mutable gives a local copy of every thing in the scope and the lambda can
    // called again with the same values in tact. Because scope is also passed by
    // reference, it affects variables outside too.
    auto e = [&] () mutable { cout << "x: " << x << "   y:" << y << endl;
        x++;
    };
    e();
    cout << "D, x in main: " << x << endl;
    cout << "D, y in main: " << y << endl;
    e();
    cout << "E, x in main: " << x << endl;
    cout << "E, y in main: " << y << endl;

    x = 10;
    y= 20;

    // you can also choose to pass only partial scope ie one or two variables
    // passing, x as read-write and y as read-only
    auto w = [&x, y] { cout << "x: " << x << "   y:" << y << endl;
                       ++x;
                       //--y; // cannot modify
                    };
    y = -99;
    w();
    cout << "F, x in main: " << x << endl;
    cout << "F, y in main: " << y << endl;
    return 0;
}
