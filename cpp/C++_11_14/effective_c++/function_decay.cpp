#include <iostream>
using namespace std;

void someFunc(int, double) {
    cout << "someFunc" << endl;
}


// T will be a function pointer type void (*)(int, double)
// because a function type decays to a function pointer type
template <typename T>
void f1(T param) {
    cout << "f1(T param)" << endl;
    (*param)(10, 2.);
}

// T will be a function type void(int, double) as it is passed by reference.
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
