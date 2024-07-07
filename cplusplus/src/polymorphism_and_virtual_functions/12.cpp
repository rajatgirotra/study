#include <iostream>
using namespace std;

class Base
{
public:
   virtual void foo()
   {
      cout<<"Base:foo()"<<endl;
   };
};

class Derv : public Base
{
private:
   void foo()
   {
      cout<<"Derv::foo()"<<endl;
   };
};

int main()
{
   Base* poBase = new Derv;
   poBase->foo();  /* Calls Derv::foo() */

   Derv* poDerv = new Derv;
   poDerv->foo(); /* ERROR: Derv::foo() is private in this context */

   delete poBase;
   delete poDerv;
 
   return 0;
}

/* 
Question:
The above example (although may not be a practical one) seems perfectly
justified going by the C++ specifications, but sometimes it makes you
feel that it breaks the access mechanism (public/protected/private) of
C++ as far as class B is concerned. That is; you are accessing the a 
private member function of Derv(foo()) through the virtual mechanism. 


Answer:
No, it does not break anything. B inherits the public interface that
comes with A. The bare fact that B declares public inheritance from A
means that it is perfectly OK from the B's point of view to expose its
functionality through that A's public interface - after all, by using
public inheritance you state that "B is A". In this case you should not
expect B to be able to hide anything that is in fact supposed to fulfil
everything what A promised. B shuld be useable everywhere where A is
expected and the above test shows this. 

*/
