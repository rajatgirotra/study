/*
The function swap() is provided to swap the values of two objects. The general implementation
of swap() is defined in <algorithm> as follows:
namespace std {
template<class T>
inline void swap(T& a, T& b) {
T tmp(a);
a = b;
b = trap;
}
}
By using this function you can have two arbitrary variables x and y swap their values by calling
std::swap(x,y);
Of course, this call is possible only if the copy constructions and assignments inside the swap()
function are possible.
The big advantage of using swap() is that it enables to provide special implementations for more
complex types by using template specialization or function overloading. These special
implementations might save time by swapping internal members rather than by assigning the
objects. This is the case, for example, for all standard containers (Section 6.1.2) and strings
(Section 11.2.8). For example, a swap() implementation for a simple container that has only
an array and the number of elements as members could look like this:
class MyContainer {
The C++ Standard Library
dyne-book 66
private:
int* elems; //dynamic array of elements
int numElems; //number of elements
public:
...
//implementation of swap()
void swap(MyContainer& x) {
std::swap(elems,x.elems);
std::swap(numElems,x.numElems);
}
...
};
//overloaded global swap() for this type
inline void swap (MyContainer& c1, MyContainer& c2)
{
c1. swap (c2); //calls implementation of swap()
}
So, calling swap() instead of swapping the values directly might result in substantial
performance improvements. You should always offer a specialization of swap() for your own
types if doing so has performance advantages.
*/


   

