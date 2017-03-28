#include <iostream>
#include <boost/shared_ptr.hpp>

using namespace std;

class A
{
   int i;

   public:
       A() : i(100)
     {}

      int getI() const
     {  return i ; }

     void setI(int pI)
      {
         i = pI;
      }
};

int main()
{
    const boost::shared_ptr<A> sp(new A());
    const boost::shared_ptr<A>& cref = sp;

    sp->setI(10);
    cref->setI(20);

    cout << sp.use_count() << endl;
    cout << cref.use_count() << endl;
    cout << sp->getI() << endl;
}

