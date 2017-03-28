/*

Whenever a class template is instantiated, the code from the class definition for the particular specialization is generated, along with all the member functions that are called in the program. Only the member functions that are called are generated. This is good, as you can see in the following program:

*/

//: C05:DelayedInstantiation.cpp
// Member functions of class templates are not
// instantiated until they're needed.

#include <iostream>
using namespace std;

template <typename T>
class Z
{
private:
   T objT;

public:

   void a()
   {
      objT.f();
   }

   void b()
   {
      objT.g();
   }
};

class X
{
public:
   void f()
   {
      cout<<"X::f()"<<endl;
   }
};

class Y
{
public:
   void g()
   {
      cout<<"Y::g()"<<endl;
   }
};

int main()
{
Z<X> zx;
zx.a();

Z<Y> zy;
zy.b();


return 0;
}
