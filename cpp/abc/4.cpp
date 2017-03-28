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

CBase b; CBase* pb;
CDerived d; CDerived* pd;

pb = dynamic_cast<CBase*>(&d);     // ok: derived-to-base
pd = dynamic_cast<CDerived*>(&b);  /* this does not work */
pd = dynamic_cast<CDerived*>(pb); /* this works !! */

return 0;
}

