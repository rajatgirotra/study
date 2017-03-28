/*
shared_array is a smart pointer that enables shared ownership of arrays. It is to shared_ptr what scoped_array is to scoped_ptr. 
*/

#include <iostream>
#include <boost/shared_array.hpp>
using namespace std;

class A
{
public:
   static int counter;

   int id;
   A() : id(++counter)
   { }

   int getID()
   { return id; }

};

int A::counter = 0;

int main()
{
   A* poA = new A[5]; // --> dont create an array on the stack like this: A arr[5]; and assign to shared_array.
			// It will lead to a problem, as at the end of the function, the array will be deleted automatically,
			// giving us a double free or corruption issue.
   boost::shared_array<A> p(poA);

   for(int i = 0; i < 5; ++i)
      cout << p[i].getID() << endl;

   return 0;
}
