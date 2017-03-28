/*
Very simple use of std::reference_wrapper
*/

#include <iostream>
#include <functional>

using namespace std;

int main() {
    int a {10}, b {20}, c {30};

    std::reference_wrapper<int> refs[] {a, b, c}; // creating an array of reference_wrappers

    for (auto& i : refs) {
        cout << i << " ";
    }
    cout << endl;
    return 0;
}
