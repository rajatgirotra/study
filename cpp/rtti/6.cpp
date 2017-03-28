/*
As you saw in the earlier program that used the hierarchy of Security classes, dynamic_cast can detect both exact types and, in an inheritance hierarchy with multiple levels, intermediate types. Here is another example.
*/


//: C08:IntermediateCast.cpp
#include <iostream>
#include <cassert>
#include <typeinfo>
using namespace std;
 
class B1 {
public:
  virtual ~B1() {}
};
 
class B2 {
public:
  virtual ~B2() {}
};
 
class MI : public B1, public B2 {};
class Mi2 : public MI {};
 
int main() {
  Mi2 mi2obj;
  B1* myb1 = 0;
  myb1 = dynamic_cast<B1*>(&mi2obj);
  B2* myb2 = 0;
  myb2 = dynamic_cast<B2*>(&mi2obj);
  MI* mymi = 0;
  mymi = dynamic_cast<MI*>(&mi2obj);

  if(myb1 && myb2 && mymi)
  {
      cout<<static_cast<void*>(&mi2obj)<<endl;
      cout<<static_cast<void*>(myb1)<<endl;
      cout<<static_cast<void*>(myb2)<<endl;
      cout<<static_cast<void*>(mymi)<<endl;
  }

  B2* b2 = new Mi2;
  Mi2* mi2 = NULL;
  MI* mi = NULL;
  B1* b1= NULL;

  mi2 = dynamic_cast<Mi2*>(b2);
  mi = dynamic_cast<MI*>(b2);
  b1 = dynamic_cast<B1*>(b2);
  assert(typeid(b2) != typeid(Mi2*));
  assert(typeid(b2) == typeid(B2*));
  assert(typeid(*b2) == typeid(Mi2));

  if( !(mi2) || !(mi) || !(b1))
     cout<<"What happened..?? "<<endl;
  delete b2;
} ///:~

/* 

This example has the extra complication of multiple inheritance (youll learn more about multiple inheritance later in this chapter, and in Chapter 9). If you create an Mi2 and upcast it to the root (in this case, one of the two possible roots is chosen), the dynamic_cast back to either of the derived levels MI or Mi2 is successful.

You can even cast from one root to the other:
  B1* b1 = dynamic_cast<B1*>(b2);
 

This is successful because B2 is actually pointing to a Mi2 object, which contains a subobject of type B1.

Casting to intermediate levels brings up an interesting difference between dynamic_cast and typeid. The typeid operator always produces a reference to a static type_info object that describes the dynamic type of the object. Thus, it doesnt give you intermediate-level information. In the following expression (which is true), typeid doesnt see b2 as a pointer to the derived type, like dynamic_cast does:
typeid(b2) != typeid(Mi2*)
 

The type of b2 is simply the exact type of the pointer:
typeid(b2) == typeid(B2*)

*/
