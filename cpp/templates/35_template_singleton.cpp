#include <iostream>
using namespace std;

template <typename T>
class Singleton
{

   Singleton(const Singleton& roSingleton);
   Singleton& operator = (const Singleton& roSingleton);

protected:
   
   Singleton()
   {
      cout<<"Singleton template c'tor running"<<endl;
   }

   virtual ~Singleton()
   {
      cout<<"Singleton template d'tor running"<<endl;
   }

public:
   
   static T& getInstance()
   {
      static T myInstance;
      return myInstance;
   }
};

class MyClass : public Singleton<MyClass>
{
   int value;

protected:
   MyClass() : value(0)
   {
      cout<<"MyClass c'tor running"<<endl;
   }

   friend class Singleton<MyClass>;
   /* This friend function is required so that you can class the MyClass c'tor which is protected from getInstance() in Singleton template class. */

public:
   int getValue() const
   {
      return value;
   }

   void setValue(int x)
   {
      value = x;
   }
};

int main()
{
   MyClass& m = MyClass::getInstance();
   cout<<"m.getValue = "<<m.getValue()<<endl;
   
   MyClass& m1 = MyClass::getInstance();
   m1.setValue(9);
   cout<<"m.getValue = "<<m.getValue()<<endl;

   return 0;
}
     
