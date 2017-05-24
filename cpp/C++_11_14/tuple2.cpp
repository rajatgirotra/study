#include <iostream>
#include <functional>
#include <tuple>
#include <string>
using namespace std;


int main() {
    int a = 10;
    tuple<const int&> t1(a); // A tuple containing one const int& with value 10. Note that the variable "a" and the variable inside tuple are SAME.

    auto x = std::get<0>(t1); // std::get<> will return you a reference type. But because we have "auto x", x will be a plain int. so x++ is not a problem, as it is just an "int"
    x++;
    cout << "x: " << x << "   a:" << a << endl;

    // The tuple_element<> function returns you the exact type as specified in the tuple declaration.
    // so y here will be const int&, referring to int in the container.
    tuple_element<0, decltype(t1)>::type y = std::get<0>(t1);
    y++;
    cout << "y: " << y << "   a:" << a << endl;

    return 0;
}
