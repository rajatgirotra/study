/*
You have already seen in 10_*.cpp how making a d'tor protected increase the level of security for shared_ptr.
This can be further increased when using a custom deletor. 

What we can do is to create a private nested class inside the class which will be used with shared_ptr.
This nested class will have a function object (i.e. operator() ), which will take a pointer to the outer class and
call delete on it.
The outer class will need to declare the nested class as its friend, because the nested class will be calling the
protected d'tor of the outer class with the "delete" statement.
*/

#include <iostream>
#include <boost/shared_ptr.hpp>
using namespace std;

class A
{
private:
   class deleter
   {
      public:
          void operator() (A* poA)
          {
             cout << "Deleting object A" << endl;
             delete poA;
          }
   };

   virtual void sing()
   {
     cout << "Lalalalalalalalala" << endl;
   }

protected:
   virtual  ~A()
   {
      cout << "A d'tor running" << endl;
   }

   friend class deleter;

public:

   static boost::shared_ptr<A> createA()
   {
      boost::shared_ptr<A> p(new A(), A::deleter());
      return p;
      /* you can't create this function outside this class as you did in 10_*.cpp
         because you access the private A::deleter() class
     */
   }
};


int main()
{
  boost::shared_ptr<A> p = A::createA();
  return 0;
}
 
