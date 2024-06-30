#include <iostream>
using namespace std;

class Base
{

public:
   int f() const { cout<<"Base::f()"<<endl;  return 1;}
   void f(string) const { cout<<"Base::f(string)"<<endl; }
};

class Derv : public Base
{

public:

//int f(int) const { cout<<"Derv::f(int)"<<endl; return 2; }
string f(string) const { cout<<"Derv::f(string)"<<endl; return "5"; }
//int f() const { cout<<"Derv::f()"<<endl; return 3; }
};

int main()
{

Derv oDerv;
//oDerv.f(5);
string abc = oDerv.f("I am rajat");

return 0;
}

/* In case of NO VIRTUAL FUNCTION, even if u redefine one of the overloaded functions of the base-class in your dervied class
all other overloaded functions become un-accessible in the derived class.

So you will have to redefine all the overloaded functions too if you want to use them. */

