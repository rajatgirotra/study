#include <iostream>
#include <functional>
#include <tuple>
#include <string>
using namespace std;


int main() {
    int a = 10;
    tuple<int&> t1(a); // A tuple containing one int& with value 10. Note that the variable "a" and the variable inside tuple are SAME.

    auto x = std::get<0>(t1); // std::get<> will return you an lvalue reference type. But because we have "auto x", x will be a plain int. so x++ is not a problem, as it is just an "int". Also incrementing x will not effect the value in the container.
    x++;
    a--; // obviously, "a" and container item are SAME. so the value will be 9.
    cout << "x: " << x << "  a:" << a << "   in container: " << std::get<0>(t1) << endl;

    // The tuple_element<> function returns you the exact type as specified in the tuple declaration.
    // so y here will be int&, referring to int in the container.
    tuple_element<0, decltype(t1)>::type y = std::get<0>(t1);
    y = y*10; // y, a, and container all are same.
    cout << "y: " << y << "  a:" << a << "   in container: " << std::get<0>(t1) << endl;

    return 0;
}
