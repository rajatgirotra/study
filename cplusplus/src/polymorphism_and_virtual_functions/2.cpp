#include <iostream>
using namespace std;

class A
{
public:
   int data;

public:

   A() : data(4)
   { };

 virtual const int& getData()
//  const int& getData()
   {
      return data;
   }

   virtual ~A()
   { cout<<"A d'tor running"<<endl; }
};

class B : public A
{
public:
   int data;

public:
   B() : data(5)
   { };

   const int& getData()
   {
      return data;
   }
};

int main()
{
cout<<"Sizeof(A) = "<<sizeof(A)<<" ... Sizeof(B) = "<<sizeof(B)<<endl;
A* poA = new A;
cout<<poA->getData()<<endl;
A* poB = new B;
B* poRealB = dynamic_cast<B*>(poB);

cout<<poB->getData()<<endl;
cout<<"Diff =  "<<poB->getData()-poA->getData()<<endl;
cout<<"poB->data = "<<poB->data;

cout<<endl<<endl<<endl;
poRealB->data = 10;
cout<<"poB->getData() = "<<poB->getData()<<endl;
cout<<"Diff =  "<<poB->getData()-poA->getData()<<endl;
cout<<poB->data<<endl;

delete poA;
delete poB;
return 0;
}
