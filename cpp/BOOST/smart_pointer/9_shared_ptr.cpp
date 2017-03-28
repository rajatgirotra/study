/*
boost::shared_ptr<T> is a reference counted smart pointer class. These smart pointers eliminate the need to write complicated logic to control the lifetime of objects shared among two or more other objects. When the reference count drops to zero, no more objects are interested in the shared object, and so it is deleted automatically. Reference-counted smart pointers can be categorized as intrusive or non-intrusive. The former expects the classes that it manages to provide certain functionality or data members with which to manage the reference count. That means designing classes with the foresight to work with an intrusive, reference-counted smart pointer class, or retrofitting. Non-intrusive, reference-counted smart pointers don't require anything of the types they manage.

A shared_ptr can be constructed from a raw pointer, another shared_ptr, a std::auto_ptr, or a boost::weak_ptr. It is also possible to pass a second argument to the constructor of shared_ptr, known as a deleter. The deleter is later called upon to handle deletion of the shared resource. This is useful for resource management where the resource is not allocated with new and destroyed with delete (we shall see examples of creating custom deleters later). After the shared_ptr has been constructed, it is used just like an ordinary pointer, with the obvious exception that it must not be explicitly deleted.

shared_ptr<T> also make it possible to store pointers to objects in Standard Library containers without risk of leaks, especially in the face of exceptions or when removing elements from the containers

*/

#include <boost/shared_ptr.hpp>
#include <iostream>
using namespace std;

class A
{
static int count;
int id;

public:
   A() : id(++count) 
   {
      cout << "A c'tor ID: "<< id << endl;
   }

   ~A()
   {
      cout << "A d'tor ID: " << id << endl;
   }

   int getID() const { return id; }
};

int A::count = 0;

template <typename T>
void print(boost::shared_ptr<T> p)
{
   cout << "print p->getID() = "<< p->getID() << "   Count: " << p.use_count() << endl;
}

int main()
{
   boost::shared_ptr<A> p(new A());
   cout << p.use_count() << endl;
   print(p);

   boost::shared_ptr<A> p1(p);

   p1.reset();

   if(p1)
   //if(p) // --> To check if this shared_ptr<T> is NULL or NOT.
	cout << "NOT NULL" << endl;

    //unique() returns tue if this shared_ptr is the sole owner of the shared resource.
    cout << boolalpha << p.unique() << endl;

   return 0;
}

/*
A simple guideline that nearly eliminates the possibility of memory leaks is: always use a named smart pointer variable to hold the result of new. Every occurence of the new keyword in the code should have the form:

shared_ptr<T> p(new Y);

If you observe this guideline, it naturally follows that you will have no explicit deletes; try/catch constructs will be rare.
Avoid using unnamed shared_ptr temporaries to save typing; to see why this is dangerous, consider this example:

void f(shared_ptr<int>, int);
int g();

void ok()
{
    shared_ptr<int> p(new int(2));
    f(p, g());
}

void bad()
{
    f(shared_ptr<int>(new int(2)), g());
}

The function ok follows the guideline to the letter, whereas bad constructs the temporary shared_ptr in place, admitting the possibility of a memory leak. Since function arguments are evaluated in unspecified order, it is possible for new int(2) to be evaluated first, g() second, and we may never get to the shared_ptr constructor if g throws an exception.

*/
