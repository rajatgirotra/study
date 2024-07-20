#include <iostream>
using namespace std;

class CBase { };
class CDerived: public CBase { };

int main()
{

CBase b; CBase* pb;
CDerived d; CDerived* pd;

pb = dynamic_cast<CBase*>(&d);     // ok: derived-to-base
pb = &d;     // ok: derived-to-base
pd = dynamic_cast<CDerived*>(&b); // -----> A

return 0;
}

/* Please note the error when u compile this out. */
/* In line A; you are trying to downcast; i.e. making a derived class pointer point to a base class object */
/* This is possible only if the source class is POLYMORPHIC. If the source type is not polymorphic, no RTTI machinery will be included in the object code
 * by the compiler to perform a dynamic_cast check at runtime. */
