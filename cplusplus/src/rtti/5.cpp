/*
The following example shows that the class name that type_info::name( ) returns is fully qualified:
*/

//: C08:RTTIandNesting.cpp
#include <iostream>
#include <typeinfo>
using namespace std;
 
class One {
  class Nested {};
  Nested* n;
public:
  One() : n(new Nested) {}
  ~One() { delete n; }
  Nested* nested() { return n; }
};
 
int main() {
  One o;
  cout << typeid(*o.nested()).name() << endl;
} ///:~
 
/*
Since Nested is a member type of the One class, the result is One::Nested.
*/
