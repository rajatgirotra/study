/*
Non-virtual methods must never be redefined by a subclass.

There are two reasons for this. First is that if the method needs to be redefined, then the subclass should not inherit from the base class in the first place. It fails to be an "is-a" of the base class.

Then there is a technical reason. A non-virtual function is statically bound and a reference to the base class will always invoke the method of the base class even if the object is derived from the base class. 

*/

#include <iostream>
using namespace std;

class Base
{
public:
   void foo()
   {
      cout<<"Base::foo()"<<endl;
   }
};

class Derv : public Base
{
public:
   void foo()
   {
      cout<<"Derv::foo()"<<endl;
   }
};

int main()
{
   Base* poBase = new Derv;
   poBase->foo();
   return 0;
}
