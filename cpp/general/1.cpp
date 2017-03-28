/*
The assignment operator should always return a reference to *this. 
Even if it does not; it still works but it is preferred that you return a reference to *this

Also the assignment operator should always check for assignment to self. 
*/

#include <iostream>
using namespace std;

class MyClass
{
private:
   int data;

   static int iCount;

   int tag;

public:
   MyClass() : data(0)
   { 
      ++iCount;
      tag = iCount;
   };

   int getData() const
   {
      return data;
   }
  
   MyClass(const MyClass& roMyClass)
   {
      data = roMyClass.data;
      ++iCount;
      tag = iCount;
   }

   MyClass operator = (const MyClass& roMyClass)
   {
      cout<<"Incoming Tag = "<<roMyClass.tag<<endl;
      if( this != &roMyClass)
      {
         this->data = roMyClass.data;
      }

      MyClass temp(*this);
      cout<<"Temp Tag = "<<temp.tag<<endl;
      return temp;
   }

   void setData(int p_data)
   {
      data = p_data;
   }

   int getTag() const
   {
      return tag;
   }
};

int MyClass::iCount = 0;

int main()
{

MyClass a, b, c;

cout<<"a.getTag() = "<<a.getTag()<<endl;
cout<<"b.getTag() = "<<b.getTag()<<endl;
cout<<"c.getTag() = "<<c.getTag()<<endl;

c.setData(10);

a = b = c;

cout<<a.getData()<<endl;
cout<<b.getData()<<endl;
cout<<c.getData()<<endl;


return 0;
}

