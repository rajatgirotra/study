#include <iostream>
#include <string>
using namespace std;

template <typename T>
struct MyWrapper {
    T& value;

 public:
    explicit MyWrapper(T& t) : value(t) {
    }

    operator T&() const {
        cout << "operator type called" << endl;
        return value;
    }

    // void operator++() {
    //     --value;
    // }
};

int main() {
    int a = 10;
    MyWrapper<int> w(a);
    cout << "Incrementing now" << endl;

    // If the operator++() is uncommented, it is used, and the value
    // will be 9. However, it operator++() is not available, the compiler
    // tries to see if it can still allow ++ operation. It sees that there
    // is a conversion operator T&() available, and it uses it and then sets
    // value to 11. So this is a nice technique if you want to wrap up some
    // object and then allow operations on the wrapped object like, cout, ++,
    // --, static_cast, assignment etc.
    ++w;
    cout << "Incremented" << endl;
    cout << "Value: " << w.value << endl;

    static_cast<int&>(w) = 20;
    cout << "After statis cast: " << w.value << endl;
    int& x = w; // possible because conversion operator is available.
    cout << "X: " << x << endl;
    return 0;
}
