/*

placement new & delete
There are two other, less common, uses for overloading operator new( ).
   1. You may want to place an object in a specific location in memory. This is especially important with hardware-oriented embedded systems where an object may be synonymous with a particular piece of hardware.
   2. You may want to be able to choose from different allocators when calling new.

Both of these situations are solved with the same mechanism: The overloaded operator new( ) can take more than one argument. As you.ve seen before, the first argument is always the size of the object, which is secretly calculated and passed by the compiler. But the other arguments can be anything you want . the address you want the object placed at, a reference to a memory allocation function or object, or anything else that is convenient for you.

The way that you pass the extra arguments to operator new( ) during a call may seem slightly curious at first. You put the argument list (without the size_t argument, which is handled by the compiler) after the keyword new and before the class name of the object you.re creating. For example,

    X* xp = new(a) X;

will pass a as the second argument to operator new( ). Of course, this can work only if such an operator new( ) has been declared.

Here.s an example showing how you can place an object at a particular location:

*/

#include <iostream>
#include <fstream>

using namespace std;

class X
{

unsigned int i;

public:

X(unsigned int ii) : i(ii)
{ cout<<"X::X() this = "<<this<<endl;
}

~X()
{
cout<<"~X::X() this = "<<this<<endl;
}

void* operator new(size_t sz, void* loc);
};

void* X::operator new(size_t, void* loc)
{
   return loc;
}

int main()
{
int *poInt = new int;
cout<<"poInt before calling placement new = "<<*poInt<<endl;

X* poX = new(poInt) X(47);
cout<<"poInt after calling placement new = "<<*poInt<<endl;

poX->X::~X();

delete poInt;

return 0;
}

/*

Notice that operator new only returns the pointer that.s passed to it. Thus, the caller decides where the object is going to sit, and the constructor is called for that memory as part of the new-expression.

Although this example shows only one additional argument, there.s nothing to prevent you from adding more if you need them for other purposes.

A dilemma occurs when you want to destroy the object. There.s only one version of operator delete, so there.s no way to say, .Use my special deallocator for this object.. You want to call the destructor, but you don.t want the memory to be released by the dynamic memory mechanism because it wasn.t allocated on the heap.

The answer is a very special syntax. You can explicitly call the destructor, as in

    xp->X::~X(); // Explicit destructor call

A stern warning is in order here. Some people see this as a way to destroy objects at some time before the end of the scope, rather than either adjusting the scope or (more correctly) using dynamic object creation if they want the object.s lifetime to be determined at runtime. You will have serious problems if you call the destructor this way for an ordinary object created on the stack because the destructor will be called again at the end of the scope. If you call the destructor this way for an object that was created on the heap, the destructor will execute, but the memory won.t be released, which probably isn.t what you want. The only reason that the destructor can be called explicitly this way is to support the placement syntax for operator new.

There.s also a placement operator delete that is only called if a constructor for a placement new expression throws an exception (so that the memory is automatically cleaned up during the exception). The placement operator delete has an argument list that corresponds to the placement operator new that is called before the constructor throws the exception. This topic will be explored in the exception handling chapter in Volume 2.

*/
