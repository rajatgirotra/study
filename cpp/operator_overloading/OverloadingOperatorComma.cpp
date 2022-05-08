/*

The comma operator is called when it appears next to an object of the type the comma is defined for. However, operator, is not called for function argument lists, only for objects that are out in the open, separated by commas. There doesnt seem to be a lot of practical uses for this operator; its in the language for consistency. Heres an example showing how the comma function can be called when the comma appears before an object, as well as after:

*/


//: C12:OverloadingOperatorComma.cpp
#include <iostream>
using namespace std;

class After {
int data;
public:
  After() : data(0) {};

  After(int p_data) : data(p_data) {};

  const After& operator,(const After& arg) const {
    cout << "After::operator(), " << data<< "   argument:  " << arg.data << endl;
    return *this;
  }
};

struct X 
{
    /*X() { cout << "X::X()"<< endl; }
    ~X() { cout << "X::~X()" << endl; }*/
};


class Before {};

const Before& operator,(int, Before& b) {
  cout << "Before::operator()," << endl;
  return b;
}

const Before& operator,(X, Before& b) {
  cout << "Before::operator with X()," << endl;
  return b;
}

int main() {
  After a(10), b(20);
  b, 2;  // Operator comma called

  Before c;
  1, c;  // Operator comma called

  X(), c;
  c, X();
} ///:~

