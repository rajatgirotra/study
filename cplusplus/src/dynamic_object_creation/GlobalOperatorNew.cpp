/*

Overloading global new & delete

This is the drastic approach, when the global versions of new and delete are unsatisfactory for the whole system. If you overload the global versions, you make the defaults completely inaccessible . you can.t even call them from inside your redefinitions.

The overloaded new must take an argument of size_t (the Standard C standard type for sizes). This argument is generated and passed to you by the compiler and is the size of the object you.re responsible for allocating. You must return a pointer either to an object of that size (or bigger, if you have some reason to do so), or to zero if you can.t find the memory (in which case the constructor is not called!). However, if you can.t find the memory, you should probably do something more informative than just returning zero, like calling the new-handler or throwing an exception, to signal that there.s a problem.

The return value of operator new( ) is a void*, not a pointer to any particular type. All you.ve done is produce memory, not a finished object . that doesn.t happen until the constructor is called, an act the compiler guarantees and which is out of your control.

The operator delete( ) takes a void* to memory that was allocated by operator new. It.s a void* because operator delete only gets the pointer after the destructor is called, which removes the object-ness from the piece of storage. The return type is void.

Here.s a simple example showing how to overload the global new and delete:

*/

#include <iostream>
#include <cstddef>
#include <new>
#include <cstdlib>
using namespace std;

void* operator new(size_t sz)
{
   cout<<"Global Operator New Bytes requested = "<<sz<<endl;
   void* m = malloc(sz);
   if(!m)
   cout<<"Out of Memory"<<endl;
   return m;
}

void operator delete(void* m) noexcept
{
   cout<<"Global Operator Delete"<<endl;
   free(m);
   return ;
}

class S
{

public:
   S() { cout<<"S::S()"<<endl; }

   ~S() { cout<<"~S::S()"<<endl; }

};

int main()
{

cout<<"Creating and destroying an int"<<endl;
int* poInt = new int(47);
delete poInt;

cout<<"Creating and destroying an S"<<endl;
S* poS = new S();
delete poS;

cout<<"Creating and destroying an array of S"<<endl;
S* poSArray = new S[3];
delete []poSArray;

return 0;
}


