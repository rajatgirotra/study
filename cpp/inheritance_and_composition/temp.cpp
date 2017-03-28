#include <iostream>
using namespace std;

class Base
{
public:
int BaseData;

public:
   Base() : BaseData(10) { cout<<"Base::Base()"<<endl; }
   ~Base() { cout<<"Base::~Base()"<<endl; }
   Base(const Base& roBase) { cout<<"Base::Base(const Base&)"<<endl; }
   Base& operator=(const Base& roBase) { cout<<"Base::Base& operator=(const Base&)"<<endl; cout<<"Basedata: "<<roBase.BaseData<<endl; return *this; }
};

class Derv
{
public:
Base oBase;
int DervData;
public:
   Derv() { cout<<"Derv::Derv()"<<endl; DervData = 20; }
   ~Derv() { cout<<"Derv::~Derv()"<<endl; }
   Derv(const Derv& roDerv) : oBase(roDerv.oBase) { cout<<"Derv::Derv(const Derv&)"<<endl; cout<<roDerv.DervData<<endl; }
   Derv& operator=(const Derv& roDerv) { oBase = roDerv.oBase; cout<<"Derv::Derv& operator=(const Derv&)"<<endl;  cout<<roDerv.DervData<<endl; return *this;}
};

class Derv2 : public Derv
{
public:
int Derv2Data;
public:
   Derv2() { cout<<"Derv2::Derv2()"<<endl; Derv2Data = 30; }
   ~Derv2() { cout<<"Derv2::~Derv2()"<<endl; }
   Derv2(const Derv2& roDerv2) : Derv(roDerv2) { cout<<"Derv2::Derv2(const Derv2&)"<<endl; }
   Derv2& operator= (const Derv2& roDerv2) { Derv::operator=(roDerv2); cout<<"Derv2::Derv2& operator= (const Derv2&)"<<endl; cout<<"Derv2Data: "<<roDerv2.Derv2Data<<endl; return *this; }
};

int main()
{
Derv2 oDerv2_1;
Derv2 oDerv2_2(oDerv2_1); 

cout<<"oDerv2_2.BaseData = "<<oDerv2_2.oBase.BaseData<<endl;
cout<<"oDerv2_2.DervData = "<<oDerv2_2.DervData<<endl;
cout<<"oDerv2_2.Derv2Data = "<<oDerv2_2.Derv2Data<<endl;

oDerv2_1 = oDerv2_2;

return 0;
}
