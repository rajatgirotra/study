/* In C++11, there were a few things that you could do with std::bind and not with lambda. But with C++14, you can do everything with lambda which you can do with std::bind, so always prefer lambda.

When using bind functions are less likely to be inlined, so its better to use lambda. Also std::bind can silently ignore arguments. I dont know what good is that; but its definitely not intuitive.

The only disadvantage with lamda is that it might produce more code than bind. since each lamda will give you a new type.
*/

#include <iostream>
#include <functional>
#include <string>
using namespace std ;
using namespace std::placeholders;

void foo(string sarg, int iarg) {
    cout << "f1 called with " << sarg << "  " << iarg << endl;
}

int main() {
   
    // 1.---------------------------------------------------------------- 
    string s = "Hello World"; 
    auto f1 = std::bind(foo, std::move(s), _1); // in c++11, std::bind can move arguments but lamndas cannot
    string s1 = "Hello World"; 
    // lambda capture initializers only available with -std=c++14 or -std=gnu++14
    auto l1 = [v = std::move(s1)] (auto iarg) {
        foo(std::move(v), iarg);
    };
    f1(10);
    l1(20);


    // 2.---------------------------------------------------------------- 
    auto f2 = std::bind(foo, "Hello", 3 + 5); // std::bind can take an expression
    auto l2 = [v = 3+5] () {
        foo("Hello", v);
    }; // c++14
    f2();
    l2();


    // 3.---------------------------------------------------------------- 
    // in c++11, you could not do perfect forwarding with lamdas, string&& arg works in C++
    // but auto&& doesnt work. and that's what perfect forwarding is
    auto l3 = [] (auto&& arg) {
        foo(std::forward<decltype(arg)>(arg), 42);
    };
    l3("Hello");

    return 0;
}
