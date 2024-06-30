#include <iostream>
#include <cstdlib>
using namespace std;

//: C14:PseudoConstructor.cpp
struct X {
  int i;
  float f;
  char c;
 const char* s;
public:
  X() : i(7), f(1.4), c('x'), s("howdy") {}
//    X() {}

    void print() const {
        cout << "i = " << i << ", f = " << f << ", c = " << static_cast<int>(c) << ", s = " << s << endl;
        }
};


int main() {
  X x;
  x.print();
  [[maybe_unused]] int i(100);  // Applied to ordinary definition
  int* ip = new int(78);
  cout << *ip << endl;

} ///:~

