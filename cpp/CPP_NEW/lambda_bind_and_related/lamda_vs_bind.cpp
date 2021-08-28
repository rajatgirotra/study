/* In C++11, there were a few things that you could do with std::bind and not with lambda. But with C++14, you can do everything with lambda which you can do with std::bind, so always prefer lambda.

When using bind, functions are less likely to be inlined, so it's better to use lambda. Also std::bind can silently ignore arguments. I don't know what good is that; but it's definitely not intuitive.

The only disadvantage with lambda is that it might produce more code than bind. since each lambda will give you a new type.
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
    auto f1 = std::bind(foo, std::move(s), _1); // in c++11, std::bind can move arguments but lambdas cannot
    // The bind expression is created, so "std::move(s) has executed already, so s is empty now"
    cout << "s: " << s << endl;

    // same with lambda now.
    string s1 = "Hello World"; 
    // lambda capture initializers only available with -std=c++14 or -std=gnu++14
    // type of v will be const string, (if lambda was mutable, type of v would be string)
    auto l1 = [v = std::move(s1), &s1] (auto iarg) {
        cout << "In lambda v before: " << v << endl;
        cout << "In lambda s1 before: " << s1 << endl;
        foo(std::move(v), iarg); // std::move(v) will give you const string&& which calls copy ctor not, move ctor
        // so v is not moved. You can do "auto& x = const_cast<string&>(v);" and then "foo(std::move(x), iarg)" if you really want move
        cout << "In lambda v after: " << v << endl;
    };
    // The lambda closure is created, so "v = std::move(s1) has executed already, so s1 is empty now"
    cout << "s1: " << s1 << endl;
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
    // in c++11, you could not do perfect forwarding with lambdas, string&& arg works in C++14
    // but auto&& doesn't work. and that's what perfect forwarding is
    auto l3 = [] (auto&& arg) {
        foo(std::forward<decltype(arg)>(arg), 42);
    };
    l3("Hello");

    return 0;
}
