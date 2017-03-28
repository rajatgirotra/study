#include <iostream>
using namespace std;

template <typename T>
class MyClass
{
   T value;

public:

   MyClass(T p_arg) : value(p_arg)
   { };

   void assign(const MyClass<T>& x) //--> Even if you remove <T> in the argument, it is implied automatically. Remove it to see for yourself.
   {
      value = x.value;
   }

   T getValue() const
   {
      return value;
   }
};

int main()
{
   MyClass<int> intClass(43);
   MyClass<int> intClass1(31);

   MyClass<float> floatClass(4.5);

   cout<<"Initially: "<<endl;
   cout<<"intClass   = "<<intClass.getValue()<<endl;
   cout<<"intClass1  = "<<intClass1.getValue()<<endl;

   intClass.assign(intClass1);
   cout<<endl<<"After:"<<endl;
   cout<<"intClass   = "<<intClass.getValue()<<endl;
   cout<<"intClass1  = "<<intClass1.getValue()<<endl;

   /* Restriction here is that argument x must have exactly the same type as the object it is called for */
   /* Now go on to study MemberTemplate1.cpp */
   intClass.assign(floatClass); 

   return 0;
}
   
