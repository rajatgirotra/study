/*

Functions with the same name occurring in different branches of a hierarchy often conflict. The following hierarchy has no such problem

*/

//: C09:Dominance.cpp

#include <iostream>
#include <string>
using namespace std;
 
class Top {
public:
  virtual ~Top() {}
  virtual void f() { cout<<"Top::f()"<<endl; }
  // void f() { cout<<"Top::f()"<<endl; }
};
 
class Left : virtual public Top {
public:
  void f() { cout<<"Left::f()"<<endl; }
};
 
class Right : virtual public Top {
#if 0
public:
  void f() { cout<<"Right::f()"<<endl; }
#endif
};
 
class Bottom : public Left, public Right {};
 
int main() {
  Bottom b;
  //b.Right::f(); // Calls Right::f()
   b.f();
} ///:~

/* Making f() virtual in Top does make a difference */
