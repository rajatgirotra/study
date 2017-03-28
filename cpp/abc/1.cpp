#include <iostream>
using namespace std;

class CBase { };
class CDerived: public CBase { };

int main()
{

CBase b; CBase* pb;
CDerived d; CDerived* pd;

pb = dynamic_cast<CBase*>(&d);     // ok: derived-to-base
pd = dynamic_cast<CDerived*>(&b); // -----> A

return 0;
}

/* Please note the error when u compile this out. */
/* In line A; you are trying to downcast; i.e. making a dervied class pointer point to a base class object */
/* This is possible only if the base class is POLYMORPHIC. */ 
