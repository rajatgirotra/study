#include <iostream>
#include <fstream>
using namespace std;

class Base
{
int BaseData;

public:
   Base() { cout<<"Base::Base()"<<endl; }

};

class Derv : public Base
{
int DervData;

public:
   Derv(int p_data) : DervData(p_data) { cout<<"Derv::Derv(int)"<<endl; }

};

int main()
{
Derv oDerv(10);
return 0;
}
