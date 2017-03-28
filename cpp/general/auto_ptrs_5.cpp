// Please open and read about auto_ptr's from the Joshuttis book.

#include <iostream>
#include <utility>
#include <memory>
#include <new>
using namespace std;

class ClassA
{
   int value;
public:
   ClassA(int p_arg = -99) : value(p_arg)
   {
      cout<<"class A c'tor"<<endl;
   };

   int getValue() const
   {
      return value;
   }
   
   ClassA(const ClassA& obj) : value(obj.value)
   {
      cout<<"class A copy c'tor"<<endl;
   }
};

class ClassB
{
private:

    const std::auto_ptr<ClassA> ptr1; //auto_ptr members
    const std::auto_ptr<ClassA> ptr2;

public:
   //constructor that initializes the auto_ptrs
   //- no resource leak possible
   ClassB (const ClassA& val1, const ClassA& val2) : ptr1 (new ClassA(val1)), ptr2(new ClassA(val2))
   {
   }

   //copy constructor
   //- no resource leak possible
   ClassB (const ClassB& x) : ptr1(new ClassA(*(x.ptr1))), ptr2(new ClassA(*(x.ptr2))) 
   {
   }

   //assignment operator
   const ClassB& operator= (const ClassB& x)
   {
      if( this != &x )
      {
         *ptr1 = *x.ptr1;
         *ptr2 = *x.ptr2;
      }
      return *this;
   }

   ClassA* getPtr1() const
   {
      return ptr1.get();
   } 

   ClassA* getPtr2() const
   {
      return ptr2.get();
   }
   //no destructor necessary
   //(default destructor lets ptr1 and ptr2 delete their objects)
};

int main()
{
   ClassA a1(10), a2(30);
   ClassB b1(a1, a2); 

   ClassB b2(b1);
   *(b2.getPtr1()) = -9876;
   *(b2.getPtr2()) = -9875;
   

   cout<<b1.getPtr1()->getValue()<<endl;
   cout<<b1.getPtr2()->getValue()<<endl;
   cout<<b2.getPtr1()->getValue()<<endl;
   cout<<b2.getPtr2()->getValue()<<endl;

   b1 = b2;
   cout<<b1.getPtr1()->getValue()<<endl;
   cout<<b1.getPtr2()->getValue()<<endl;
   return 0;
}

