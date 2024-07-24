#include <iostream>
using namespace std;

class Integer
{
unsigned int data;

public:
   Integer(unsigned int arg = 9) : data(arg)
   { };

   friend Integer& operator = (Integer& left, const Integer& right);

   void display() const
   {
      cout<<"Data = "<<data<<endl;
   }
};

Integer& operator = (Integer& left, const Integer& right)
{
    left.data = right.data;
    return left;
}

int main()
{
Integer a1(3);
Integer a2;
cout<<"a1"<<endl;
a1.display();
cout<<"a2"<<endl;
a2.display();

a2 = a1;
cout<<"a1"<<endl;
a1.display();
cout<<"a2"<<endl;
a2.display();

return 0;
}

