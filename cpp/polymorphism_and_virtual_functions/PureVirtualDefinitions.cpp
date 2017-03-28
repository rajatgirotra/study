/*

   Pure virtual definitions

   It.s possible to provide a definition for a pure virtual function in the base class. You.re still telling the compiler not to allow objects of that abstract base class, and the pure virtual functions must still be defined in derived classes in order to create objects. However, there may be a common piece of code that you want some or all of the derived class definitions to call rather than duplicating that code in every function.

   Here.s what a pure virtual definition looks like:

 */

#include <iostream>
using namespace std;

class Base
{
   public:
      virtual void speak() = 0;
};

void Base::speak()
{
   cout<<"Base::speak"<<endl;
   cout<<"this in Base = "<<this<<endl;
}
class Derv : public Base
{
   public:
      void speak()
      {
         cout<<"this in Derv = "<<this<<endl;
         Base::speak();
      }
};

class Derv_2 : public Base
{
   public:
      void speak()
      {
         cout<<"this in Derv_2 = "<<this<<endl;
         Base::speak();
      }
};

int main()
{
//! Base oBase; // This is not allowed; since Base has a pure virtual function */
   Base* poBase = new Derv;
   poBase->speak();
   Derv oDerv;
   Derv_2 oDerv2;
   oDerv.speak();
   oDerv2.speak();
   return 0;
}
