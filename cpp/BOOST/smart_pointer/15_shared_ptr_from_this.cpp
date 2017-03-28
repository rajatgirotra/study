/*
the solution comes from a smart pointer component thats called boost::weak_ptr. A weak_ptr is an observer of shared_ptrs; it just silently sits and watches them, but does not affect the reference count. By storing a weak_ptr to this as a member of the class, it's possible to retrieve a shared_ptr to this on demand. To relieve you from the tedium of having to write the code for storing a weak_ptr to this and subsequently obtain a shared_ptr from that weak_ptr, Boost.Smart_ptr provides a helper class for this task, called enable_shared_from_this. Simply have your class derive publicly from enable_shared_from_this, and then use the function shared_from_this whenever you need to access the shared_ptr that is managing this. Here's an example that demonstrates how enable_shared_from_this is used:
 */


#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <iostream>
using namespace std;

class A;

void do_something(boost::shared_ptr<A> p)
{
   cout << &p << endl;
}

class A : public boost::enable_shared_from_this<A>
{
public:
   void do_stuff()
   {
      do_something(shared_from_this());
   }
 
};

int main()
{
   boost::shared_ptr<A> p (new A());
   p->do_stuff();
   p->do_stuff();

   return 0;
}

/*
in shared_from_this, the weak_ptr is automatically converted to a shared_ptr increasing the ref. count by one, thereby ensuring the object is not deleted
when returning from do_stuff().
*/
