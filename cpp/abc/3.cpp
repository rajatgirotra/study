#include <iostream>
using namespace std;

class CBase 
{ 
private:
   int a;
public:

   CBase() : a(10)
   { };

   virtual void dummy()
   {
      cout<<"CBase::dummy()"<<endl;
   };
};
class CDerived: public CBase
{
public:
   int b;

public:
  
   CDerived() : b(20)
   { };
 
   void display()
   {
     cout<<"CDerived::display()"<<endl;
     cout<<"b = "<<b<<endl;
   };
   
};

int main()
{

CBase b; CBase* pb;
CDerived d; CDerived* pd;

cout<<"&b = "<<&b<<endl;

pb = dynamic_cast<CBase*>(&d);     // ok: derived-to-base
pd = static_cast<CDerived*>(&b);  /* This is allowed; but you are responsible for the mess */

/* pd does not point to a valid complete object of type CDerived; so de-referencing might cause issues. */

cout<<"pd = "<<static_cast<void*>(pd)<<endl;
pd->display();
pd->b = 100;
pd->display();

cout<<endl;
cout<<"&d = "<<static_cast<void*>(&d)<<endl;
cout<<"pb = "<<static_cast<void*>(pb)<<endl;

return 0;
}
