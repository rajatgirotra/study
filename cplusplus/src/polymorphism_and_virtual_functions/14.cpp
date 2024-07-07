#include <iostream>
using namespace std;

class Base
{
public:
    void foo()
   {
      cout<<"Base::foo()"<<endl;
   }

public:
   void call()
   {
      this->foo();
   }
};

class Derv : protected Base
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
   //poBase->call(); 

   delete poBase;
   return 0;
}
