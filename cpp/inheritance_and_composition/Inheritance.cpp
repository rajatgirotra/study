//: C14:Inheritance.cpp
// Simple inheritance
#include "Useful.h"
#include <iostream>
using namespace std;

class Y : public X {
  int i; // Different from X's i
public:
  Y() { i = 10; }
  int change() {
    i = permute() + 1; // Different name call
    return i;
  }
  void set(int ii) {
    i = ii;
    X::set(ii); // Same-name function call
  }
  int myfunc()
  {
      return X::read();
  };

  int getLocal() const 
  { return i; };
 
};

int main() {
  cout << "sizeof(X) = " << sizeof(X) << endl;
  cout << "sizeof(Y) = "
       << sizeof(Y) << endl;
  Y D;
  cout<<"Y.getLocal() returned = "<<D.getLocal()<<endl;
  D.change();
  // X function interface comes through:
  cout<<"Y.getLocal() returned = "<<D.getLocal()<<endl;
  cout<<"D.read() returned = "<<D.read()<<endl;
  D.permute();
  cout<<"D.read() returned = "<<D.read()<<endl;
  // Redefined functions hide base versions:
  cout<<"D.myfunc() returned = "<<D.myfunc()<<endl;
  D.set(12);
  cout<<"D.read() returned = "<<D.read()<<endl;
  cout<<"D.myfunc() returned = "<<D.myfunc()<<endl;
  cout<<"D.getLocal() returned = "<<D.getLocal()<<endl;
} ///:~

