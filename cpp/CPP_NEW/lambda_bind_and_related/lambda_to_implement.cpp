/* The best way to implement lambda (with perfect forwarding) is: */

#include <iostream>
using namespace std;

void func(const char* s) {
    cout << s << endl;
}

// 1st implementation, this is a variable template. see Jason Turner youtube episode on variable templates
template <typename... Args>
auto closure = [] (Args&&... args) {
    func(std::forward<decltype(args)>(args)...);
};

// 2nd implementation
auto variadic_lambda = [](auto&&... params) {
    func(std::forward<decltype(params)>(params)...);
};

int main() {
    closure<const char*>("Hello World");
    variadic_lambda("Hello World");
}

/*
 * 2nd implementation
 * struct SomeFunctionObject
 * {
 *     template <typename... Args>
 *     auto operator() (Args&&... args) const;
 * };
 */
