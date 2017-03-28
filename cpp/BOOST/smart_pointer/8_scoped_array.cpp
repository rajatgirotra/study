/*
boost::scoped_array<T> is exactly similar to scoped_ptr<T> except that it handles deletion of dynamically allocated arrays.
This means that it does delete[] instead of delete in its d'tor.

Use scoped_array when you are dynamically allocating an array of fixed size. If the size is variable, then use std::vector which is much more
powerful.

T & operator[](std::ptrdiff_t i) const; // never throws
Returns a reference to element i of the array pointed to by the stored pointer. Behavior is undefined and almost certainly undesirable if the stored pointer is 0, or if i is less than 0 or is greater than or equal to the number of elements in the array.
*/

#include <boost/scoped_array.hpp>
#include <iostream>
#include <string>
using namespace std;

class A
{
static int i;
int id;
public:
   A() : id(++i)
   {
      cout << "A c'tor: " << id << endl;
   }

   ~A()
   {
      cout << "A d'tor: " << id << endl;
   }

   int getID() const { return id; }
};

int A::i = 0;

int main()
{
   boost::scoped_array<A> sa(new A[2]);
   cout << "sa[0].getID = " << sa[0].getID() << endl;
   cout << "sa[0].getID = " << sa[1].getID() << endl;
   return 0;
}


