/*

The RTTI mechanisms must work properly with all the complexities of multiple inheritance, including virtual base classes (discussed in depth in the next chapteryou may want to come back here after reading Chapter 9):

*/


//: C08:RTTIandMultipleInheritance.cpp
#include <iostream>
#include <typeinfo>
using namespace std;
 
class BB {
public:
  virtual void f() {}
  virtual ~BB() {}
};
 
class B1 : virtual public BB {};
class B2 : virtual public BB {};
class MI : public B1, public B2 {};
 
int main() {
  cout<<"Size of BB = "<<sizeof(BB)<<endl;
  cout<<"Size of B1 = "<<sizeof(B1)<<endl;
  cout<<"Size of B2 = "<<sizeof(B2)<<endl;
  cout<<"Size of MI = "<<sizeof(MI)<<endl;
  BB* bbp = new MI; // Upcast
  // Proper name detection:
  cout << typeid(*bbp).name() << endl;
  // Dynamic_cast works properly:
  MI* mip = dynamic_cast<MI*>(bbp);
  // Can't force old-style cast:
  //! MI* mip2 = (MI*)bbp; // Compile error ; cannot convert from BB* to MI* via virtual base BB.
} ///:~


/*

The typeid( ) operator properly detects the name of the actual object, even through the virtual base class pointer. The dynamic_cast also works correctly. But the compiler wont even allow you to try to force a cast the old way:
MI* mip = (MI*)bbp; // Compile-time error
 

The compiler knows this is never the right thing to do, so it requires that you use a dynamic_cast.

The output of the sizes remind us that a class an have more than one VPTR's as in this case.

*/
