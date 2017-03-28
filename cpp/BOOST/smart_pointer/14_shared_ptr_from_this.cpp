/*
Create a class A. Create a public function do_stuff(). From this function, 
call an ordinary function which takes a shared_ptr to your class and prints "Hello World"
*/

#include <boost/shared_ptr.hpp>
#include <iostream>
using namespace std;

class A;

void do_something(boost::shared_ptr<A> p)
{
   cout << &p << endl;
}

class A
{
public:
   void do_stuff()
   {
      boost::shared_ptr<A> p (this);
      do_something(p);
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
When you run this program u realise that this program core - dumps beacuse you are putting the same object
in two different shared_ptr. So each will call delete on the object. i.e. double deletion.

Read 15_*.cpp to check for solution.
*/
