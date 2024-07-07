#include <iostream>
using namespace std;

class A
{
private:
   int data;

public:

   A() : data(4)
   { };

  const int getData() 
   {
      return data;
   }
};

class B : public A
{
private:
   int data;

public:
   B() : data(5)
   { };

   const int getData()
   {
      return data;
   }
};

int main()
{
cout<<"Sizeof(A) = "<<sizeof(A)<<" ... Sizeof(B) = "<<sizeof(B)<<endl;

A* poA = new A;
B* poB = new B;
cout<<"poA->getData() = "<<poA->getData()<<"   poB->getData() = "<<poB->getData()<<endl;

delete poA;
delete poB;

return 0;
}

/* This code is understandable... :-) */
