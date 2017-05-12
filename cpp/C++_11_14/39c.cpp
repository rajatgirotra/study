#include <iostream>
#include <vector>
#include <list>
#include <functional>

using namespace std;

int main() {
    std::vector<double> v(5, 10.3);

    auto ref = std::ref(v); // ref will be of type std::reference_wrapper<std::vector<double>>
    std::vector<std::reference_wrapper<double>> rwd(v.begin(), v.end()); // this is different from above.

    std:vector<double>& ref2 = v;

    cout << rwd[0] << endl;
    cout << ref2[0] << endl;
    cout << ref.get()[0] << endl; // wont work unless we say ref.get()[0]

    // all rwd, ref, ref2 are different
    return 0;
}

/* One very good habbit is to use std::ref(), std::cref() when passing function objects. Instead of creating new function objects, just use these functions which is same as pointer passing and is fast. A lot of algorithm expect functors where you can use these helper functions

unsigned arr[10];
std::mt19937 myEngine;
std::generate_n( arr, 10, std::ref(myEngine) );

*/
