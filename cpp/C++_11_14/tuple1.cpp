#include <iostream>
#include <functional>
#include <tuple>
#include <string>
using namespace std;

// A tuple is a generalization of the concept of pairs. It is used to store different types known at compile time.

int main() {
    const int a = 10;
    tuple<const int> t1(a); // A tuple containing one const int with value 10. Note that the variable "a" and the variable inside tuple are different.

    auto x = std::get<0>(t1); // std::get<> will return you a reference type. But because we have "auto x", x will be a plain int. so x++ is not a problem, as it is not const.
    x++;
    cout << "x: " << x << "   a:" << a << endl;

    // The tuple_element<> function returns you the exact type as specified in the tuple declaration.
    // so y here will be const int, so cannot increment.
    tuple_element<0, decltype(t1)>::type y = std::get<0>(t1);
    y++;
    cout << "y: " << y << "   a:" << a << endl;

    return 0;
}
