#include <iostream>
using namespace std;

class Base
{

public:

   virtual void foo()
   { 
      cout<<"Base::foo()"<<endl;
   };
};

class Derv : protected Base
// class Derv : private Base
{
public:
    void foo()
    {
       cout<<"Derv::foo()"<<endl;
    }
};

int main()
{
Base* poBase = new Derv();  // --> This line is the problem. If you inherit protectedly or privately, you are basically 
//NOT in inheriting the interface of the Base class. So a the base class pointer can't point to the derived class object.


poBase->foo();
delete poBase;
return 0;
}


