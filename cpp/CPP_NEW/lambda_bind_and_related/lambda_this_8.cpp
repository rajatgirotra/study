/*
 * c++17 allows capturing *this in the lambda introducer []. Before c++17, you could capture only the "this" pointer by value[=] or by reference [&]
 * which meant you essentially were working with the same object inside the lambda. This could be a problem in cases where the lambda lifetime
 * exceeded the object lifetime. capturing [*this] will create a copy of the object, and you can safely work with it.
 * in c++14 you can also capture *this using generic lambda but its extra typing. [objCopy=*self]
 */

#include <iostream>
#include <functional>
#include <type_traits>
using namespace std;

struct Baz {
    auto foo() {
//        return [=] { std::cout << s << '\n'; };
        return [obj = *this] { std::cout << obj.s << '\n'; };
//        return [*this] { std::cout << s << '\n'; };
    }
    std::string s;
};
int main() {
    auto f1 = Baz{"This is a valid string"}.foo(); // temporary Baz object destroyed after this line but we access it in the next line
    f1();
}
