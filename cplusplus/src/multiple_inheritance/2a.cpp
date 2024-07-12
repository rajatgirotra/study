#include <iostream>
#include <string>
using namespace std;

class Base
{ public: 
    int BaseData;
};

class Derv : public Base
{ 
 public:
   int DervData;
};

//class Derv2 : public Derv
class Derv2 : public Base
{ 
 public:
   int Derv2Data;
};

int main()
{
Derv2 objDerv2;
Base*  poBase = NULL;
Derv*  poDerv = NULL;
[[maybe_unused]] Derv2* poDerv2 = NULL;

poBase = &objDerv2;
cout<<"Address of objDerv2 = "<<&objDerv2<<endl;
cout<<"Address in poBase  = "<<poBase<<endl;

//poDerv = &objDerv2;
cout<<"Address in poDerv  = "<<poDerv<<endl;
return 0;
}
