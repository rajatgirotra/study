#include <iostream>
using namespace std;

class A
{
private:
   int data;

public:

   A() : data(4)
   { };

 virtual const int getData() const
   {
      cout<<"Inside A::getData().. this pointer = "<<this<<endl;
      return data;
   }
};

class B : public A
{
public:
   int data;

public:
   B() : data(5)
   { };

   const int getData() const
   {
      cout<<"Inside B::getData().. this pointer = "<<this<<endl;
      return data;
   }
};

int main()
{
cout<<"Sizeof(A) = "<<sizeof(A)<<" ... Sizeof(B) = "<<sizeof(B)<<endl;

A* poA = new B;
cout<<"poA->getData() = "<<poA->getData()<<endl; /* Prints 5 */
cout<<"poA->data = "<<poA->data<<endl;  /* Prints 4.. why?? */

delete poA;

return 0;
}

/*
Why is there a difference in output */

