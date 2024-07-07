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
      return data;
   }
};

int main()
{
cout<<"Sizeof(A) = "<<sizeof(A)<<" ... Sizeof(B) = "<<sizeof(B)<<endl;


return 0;
}

/* Why is the size of class B 8 bytes?? */
