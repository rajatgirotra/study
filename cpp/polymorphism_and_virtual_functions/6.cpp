#include <iostream>
using namespace std;

class A
{
private:
   int data;

public:

   A() : data(4)
   { };

  const int getData() const
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

   const int getData() const
   {
      cout<<"Inside B::getData().. this pointer = "<<this<<endl;
      return A::getData();
   }
};

int main()
{
cout<<"Sizeof(A) = "<<sizeof(A)<<" ... Sizeof(B) = "<<sizeof(B)<<endl;

B* poB = new B;
cout<<"poB->getData() = "<<poB->getData()<<endl;

delete poB;

return 0;
}

/*
Consider the code snippet below

1. Why does the size of B show 8 bytes. In public inheritance, the public and protected members of the base class become the public members of the derived class. But class A has no public or protected data. How does the size of the class object increase from 4 to 8 ??

2. Second when i call A::getData() inside, B's getData() method, it outputs "4" as a result. But the this pointer printed inside A::getData() points to object B. How does it display "4" as output then, Shouldn't it display "5" ??

*/
