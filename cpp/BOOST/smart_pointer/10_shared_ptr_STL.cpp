/* Using boost::shared_ptr with STL containers
  This is a very good example and dont miss the explanation in the end. */

#include <boost/shared_ptr.hpp>
#include <iostream>
#include <vector>
#include <typeinfo>
using namespace std;

class A
{
public:
   virtual void sing() = 0;

protected:
   //virtual ~A();
   ~A();
};

A::~A() 
{
   cout << "A d'tor running" << endl;
}

class B : public A
{
public:
   void sing();

   ~B();
};

void B::sing()
{
   cout << "Sa Re Ga Ma Pa Dha Ni Sa.." << endl;
}

B::~B()
{
   cout << "B d'tor running" << endl;
}

boost::shared_ptr<A> createA()
{
   return boost::shared_ptr<A> (new B());
}

void get_raw_pointer(A* poA)
{
   // delete poA;  ---> A
   #if 0
   B* poB = dynamic_cast<B*>(poA);
   delete poB;
   poB = 0;
   #endif
}


int main()
{

   typedef std::vector<boost::shared_ptr<A> > container_type;
   typedef container_type::iterator iterator;

   container_type container;
   int i = 0;

   for(i = 0; i < 10; ++i)
   {
      container.push_back(createA());
   }

   iterator it = container.begin();
   while(it != container.end())
   {
      (*it)->sing();
      ++it;
   }

   get_raw_pointer(container[0].get());

}

/*
Had we been using raw pointers as elements, the objects would need to be manually deleted. In the example, this deletion is automatic, because the reference count of each shared_ptr in the container is 1 as long as the vector is kept alive; when the vector is destroyed, the reference counters all go down to zero, and the objects are deleted. 

It is interesting to note that even if the destructor of A had not been declared virtual, shared_ptr would have correctly invoked the destructor of B! 
So if you remove the virtual keyword in "virtual ~A(), it wont make any difference to the output. I am sure this is because somewhere in the code for shared_ptr.hpp, we are 
converting the type from A* to B*; that's why the d'tor of A is also getting called. Actually the shared+ptr class provides the following c'tor.

template<class Y>
explicit shared_ptr(Y * p);

Here p must be convertible to T* & Y must be a complete type. This constructor has been changed to a template in order to remember the actual pointer type passed. The destructor will call delete with the same pointer, complete with its original type, even when T does not have a virtual destructor, or is void.


A powerful technique is demonstrated in the example, and it involves the protected destructor in A. Because the function createA returns a shared_ptr<A>, it won't be possible to invoke delete on the pointer returned by shared_ptr:: get. This means that if the pointer in the shared_ptr is retrievedperhaps in order to pass it to a function expecting a raw pointerit won't be possible to accidentally delete it, which would wreak havoc. So, how is it that the shared_ptr is allowed to delete the object? It's because of the actual type of the pointer, which is B; B's destructor is not protected. This is a very useful way of adding extra safety to objects kept in shared_ptrs.

SO IN GENERAL IT IS A GOOD PRACTICE TO MAKE THE D'TOR OF A CLASS WHICH IS USED WITH SHARED_PTR AS PROTECTED FOR ADDED SECURITY & TO MAKE THE SHARED_PTR CLASS AS ABSTRACT LIKE WE HAVE DONE HERE.

Uncomment the first line in get_raw_pointer() and you'll understand what i am saying.
*/


