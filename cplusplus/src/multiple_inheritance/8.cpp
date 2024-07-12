/*

Breaking the tie; if you don't understand what this is; read 7.cpp first

*/

//: C09:AmbiguousName.cpp {-xo}
#include <iostream>
#include <string>
using namespace std;
 
class Top {
public:
  virtual ~Top() {}
};
 
class Left : virtual public Top {
public:
  void f() {}
  int f(string) { return -99; }
};
 
class Right : virtual public Top {
public:
  int f(string) { return 0;}
};
 
class Bottom : public Left, public Right {

public:
   //using Right::f;

};
 
int main() {
  Bottom b;
  b.Left::f();
  cout << b.Right::f("") << endl;
  //b.f("ABC");
} ///:~
 
/*

The class Bottom has inherited two functions of the same name (the signature is irrelevant, since name lookup occurs before overload resolution), and there is no way to choose between them. The usual technique to disambiguate the call is to qualify the function call with the base class name:

*/
