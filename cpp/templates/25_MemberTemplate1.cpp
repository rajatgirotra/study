#include <iostream>
using namespace std;

template <typename T>
class MyClass
{
   T value;

public:

   MyClass(T p_arg) : value(p_arg)
   { };

   /* make this a member template */
   template <typename X>
   void assign(const MyClass<X>& x)
   {
      value = x.getValue();
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

   /* This call should not produce a compilation error now */
   intClass.assign(floatClass); 
   cout<<endl<<"Later:"<<endl;
   cout<<"floatClass   = "<<floatClass.getValue()<<endl;
   cout<<"intClass     = "<<intClass.getValue()<<endl;


   return 0;
}
   
