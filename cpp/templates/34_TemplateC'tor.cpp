/*

A special form of a member template is a template constructor. Template constructors are usually
provided to enable implicit type conversions when objects are copied. Note that a template
constructor does not hide the implicit copy constructor. If the type matches exactly, the implicit
copy constructor is generated and called. For example:

*/

#include <iostream>
using namespace std;

template <typename T>
class MyClass
{
   T value;

public:

   MyClass(T p_arg) : value(p_arg)
   {
     cout<<"MyClass C'tor "<<endl;
   }

   /* Template C'tor */
   template <typename U>
   MyClass(MyClass<U>& roU);

   /* Default Copy C'tor */
   MyClass (MyClass& roMyClass);

   T getValue() const
   {
      return value;
   }
};

template <typename T>
template <typename U>
MyClass<T>::MyClass(MyClass<U>& roU)
{
   cout<<"Inside Template c'tor "<<endl;
   value = roU.getValue();
}

template <typename T>
MyClass<T>::MyClass(MyClass& roMyClass)
{
   cout<<"Inside default Copy c'tor "<<endl;
   value = roMyClass.value;
}

int main()
{
   MyClass<double> d1(10.67);
   MyClass<double> d2(d1);

   MyClass<int> i1(d1);
   return 0;
}
   
   
