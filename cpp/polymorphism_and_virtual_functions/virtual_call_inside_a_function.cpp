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

  virtual void bar()
  {
     cout<<"Base::bar()"<<endl;
  }

  void call()
  {
     bar();
  }
};

class Derv : public Base
{
public:
   Derv()
   {
      cout<<"Derv::Derv()"<<endl;
      foo();
   }
   
   void foo()
   {
      cout<<"Derv::foo()"<<endl;
   }

   void bar()
   {
      cout<<"Derv::bar()"<<endl;
   }
};

int main()
{
//Base oBase;
//Derv oDerv;

//Base* poBase[] = { &oBase, &oDerv };

 Base* poBase = new Derv;

 poBase->call();

 delete poBase;
 return 0;
}


