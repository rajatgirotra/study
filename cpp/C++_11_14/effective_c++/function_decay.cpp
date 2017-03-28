#include <iostream>
using namespace std;

void someFunc(int, double) {
    cout << "someFunc" << endl;
}

template <typename T>
void f1(T param) {
    cout << "f1(T param)" << endl;
    param(10, 2.);
}

template <typename T>
void f2(T& param) {
    cout << "f2(T& param)" << endl;
    param(10, 3.);
}
    
int main() {
    f1(someFunc);
    f2(someFunc);
    return 0;
}
