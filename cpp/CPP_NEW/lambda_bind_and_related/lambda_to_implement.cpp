/* The best way to implement lambda (with perfect forwarding) is: */

#include <iostream>
using namespace std;

int func(const char* s) {
    cout << s << endl;
    return 5;
}

template <typename... Args>
auto closure = [] (Args&&... args) {
    return func(std::forward<decltype(args)>(args)...);
};

int main() {
    cout << closure<const char*>("Hello World") << endl;
}
