#include <iostream>
using namespace std;

const int a = 200; //In C++, const defaults to internal linkage
//int a = 200; //Without the const, we will get multiple definition error as 'a' is defined as global variable in a1.cpp also
//extern const int a = 200; //with the extern keyword, you force the const to have external linkage again.

extern int foo(); // tell the compiler that foo() is defined in another translation unit

int main() {
  cout << "a in foo(): " << foo() << endl;
  cout << "a in a2.cpp: " << a << endl;
  return 0;
}
