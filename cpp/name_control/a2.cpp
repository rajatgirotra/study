#include <iostream>
using namespace std;

//int a = 200; //In C++, const defaults to internal linkage
const int a = 200; //In C++, const defaults to internal linkage

extern int foo();


int main() {
  cout << foo() << endl;
  cout << a << endl;
  return 0;
}
