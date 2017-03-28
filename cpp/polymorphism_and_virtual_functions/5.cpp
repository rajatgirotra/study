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
      cout<<"Inside A::getData().. this pointer = "<<this<<endl;
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
      cout<<"Inside B::getData().. this pointer = "<<this<<endl;
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

/* This code is understandable... :-) 
   The address's of the this pointer are different.. understandably so.. :) */

/* Also carefully note the output. It will help yo uunderstand cascading in C++. The cout expression is evaluated from right to left.
Actually unless the entire cout<<... line is completely processed; no output appears on the screen.
*/
