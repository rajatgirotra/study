#include <iostream>
using namespace std;

class Base
{
public:
  
  Base()
  {
     cout<<"Base::Base()"<<endl;
     foo();
  }
  virtual void foo()
  {
      cout<<"Base::foo()"<<endl;
  }

  virtual ~Base() {}
};

class Derv : public Base
{
public:
   Derv()
   {
      cout<<"Derv::Derv()"<<endl;
      foo();
   }
   
#if 1
   void foo()
   {
      cout<<"Derv::foo()"<<endl;
   }
#endif
};

int main()
{
//Base oBase;
//Derv oDerv;

//Base* poBase[] = { &oBase, &oDerv };

 Base* poBase = new Derv;
 delete poBase;
 return 0;
}


