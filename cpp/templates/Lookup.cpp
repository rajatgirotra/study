//: C05:Lookup.cpp
// Only produces correct behavior with EDG,
// and Metrowerks using a special option.
#include <iostream>
using std::cout;
using std::endl;
 
void f(double) { cout << "f(double)" << endl; }
 
template<class T> class X {
public:
  void g() { f(1); }
};
 
void f(int) { cout << "f(int)" << endl; }
 
int main() {
  X<int>().g();
} ///:~

