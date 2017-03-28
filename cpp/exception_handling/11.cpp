/*
Auto Ptr 

Since dynamic memory is the most frequent resource used in a typical C++ program, the standard provides an RAII wrapper for pointers to heap memory that automatically frees the memory. The auto_ptr class template, defined in the <memory> header, has a constructor that takes a pointer to its generic type (whatever you use in your code). The auto_ptr class template also overloads the pointer operators * and -> to forward these operations to the original pointer the auto_ptr object is holding. So you can use the auto_ptr object as if it were a raw pointer. Heres how it works:

The good thing about auto_ptr is that if the programmer forgets to free the object , then it takes care of it automatically
*/

#include <iostream>
#include <memory>
#include <cstddef>
using namespace std;

class Foo
{
private:
   int i;

public:
  Foo(int i = 0) : i(i)
  { cout<<"Foo::Foo(int i = 0)"<<endl; };

  static void* operator new(size_t size)
  {
     void* poMem = ::operator new(size);
     cout<<"Allocating memory of "<<size<<" bytes at address "<<poMem<<endl;
     return poMem;
  }

  static void operator delete(void* poMem)
  {
     cout<<"Deallocating memory at address "<<poMem<<endl;
     ::operator delete(poMem);
  } 

  int getVal() const { return i; }
};

int main()
{
auto_ptr<Foo> poFoo(new Foo(9));
cout<<"The Value is: "<<poFoo->getVal()<<endl;
return 0;
}

/* 

A smart pointer is an object of a class that behaves like a pointer. Since such a class could have more features built into it as compared to a typical pointer; we call it a smart pointer. We mostly use the smart pointer to wrap it around some other class to make that class pointer safe. 

So we could have a class say Object which we want to make pointer safe; we could have another class say Object container that hold a vector of Object* type. Then we could have our Smart POinter class that holds a refernce to the Object container; and  overloads the -> operator to return an Object* from the vector list held by Object container class.
*/
