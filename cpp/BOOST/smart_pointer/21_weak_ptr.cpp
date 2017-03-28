/* A weak pointer is just an observer of a shared pointer. It points to the same object as the shared_ptr but does not take ownership. i.e. the reference count of the shared_ptr is not incremented. A weak_ptr can be created by passing the shared_ptr as an argument to its c'tor.
The weak_ptr class provides a function "bool expired()" which return true if the underlying shared_ptr has been deleted, false otherwise.

The shared_ptr class on deleting the underlying object also sets the weak_ptr's pointer to null; thus preventing any dangling pointer issues.
weak_ptr also provides a function "lock()" which returns a shared_ptr and the reference count is incremented as expected.

You can use a weak_ptr just as you use a shared_ptr.
*/

#include <iostream>
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include <cassert>
using namespace std;

class A
{};

int main() {
	boost::weak_ptr<A> w;
	assert(w.expired());
	{
		boost::shared_ptr<A> p(new A());
		assert(p.use_count() == 1);
		w = p;
		assert(p.use_count() == w.use_count());
		assert(p.use_count() == 1);
		
		boost::shared_ptr<A> p2(p);
		assert(p2 == p);
	}
	assert(w.expired());
	boost::shared_ptr<A> p3(w.lock());
	assert(!p3); //p3 will be null as w is expired.
}
