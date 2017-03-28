#include <iostream>
using namespace std;

class CBase { 
public:
   virtual void dummy()
   { cout<<"CBase::dummy"<<endl; }
};
class CDerived: public CBase { };

int main()
{

CBase b; CBase* pb = 0;
CDerived d; CDerived* pd = 0;

pb = dynamic_cast<CBase*>(&d);     // ok: derived-to-base
pd = dynamic_cast<CDerived*>(&b);  /* this does not work */
if(pd == 0) cout<<"pd is 0"<<endl;
pd = dynamic_cast<CDerived*>(pb); /* this works !! */

return 0;
}

/*
When a class is polymorphic, dynamic_cast performs a special checking during runtime to ensure that the expression yields a valid complete object of the requested class: this is not the case in the 2nd statement.

Remember, even if a class has nothing but a single virtual destructor, the class becomes polymorphic.
i.e. you can use dynamic_casts and rtti with it.
*/
