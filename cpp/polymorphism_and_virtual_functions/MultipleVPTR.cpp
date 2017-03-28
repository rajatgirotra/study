#include <iostream>
#include <string>
using namespace std;

class BB
{
public:
   virtual void a0()
   {
      cout<<"BB::a0()"<<endl;
   }
};

class B1 : virtual public BB
{
public:
   virtual void a1()
   {
      cout<<"B1::a1()"<<endl;
   }
};

class B2 : virtual public BB
{
public:
   virtual void a2()
   {
      cout<<"B2::a2()"<<endl;
   }
};

class MI : public B1, public B2 
{

};

int main()
{
   cout<<"Size of BB = "<<sizeof(BB)<<endl;
   cout<<"Size of B1 = "<<sizeof(B1)<<endl;
   cout<<"Size of B2 = "<<sizeof(B2)<<endl;
   cout<<"Size of MI = "<<sizeof(MI)<<endl;

   MI objMI;
   B1* poB1 = dynamic_cast<B1*>(&objMI);
   B2* poB2 = dynamic_cast<B2*>(&objMI);

   poB1->a1(); // -- We need MI class to have two VPTR's; one pointing to VTABLE for B1 and one pointing to VTABLE for B2.
   poB2->a2();

   poB1->a0();
   poB2->a0();

   return 0;
}

