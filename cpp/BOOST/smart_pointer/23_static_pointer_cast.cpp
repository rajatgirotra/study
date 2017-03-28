#include <iostream>
#include <boost/shared_ptr.hpp>
#include <string>
using namespace std;
using namespace boost;

class Base {
public:
	virtual ~Base() { cout << "Base::~Base()" << endl; };
};

class A : public Base {
private:
   char* data;

public:
   A() {
	cout << "A::c'tor" << endl;
       data = new char[100];
   }

   ~A() {
	cout << "A::d'tor" << endl;
     delete[] data;
    }
};

int main()
{
   boost::shared_ptr<Base> a(new A());

   //boost::shared_ptr<Base> b(static_cast<Base*>(a.get()));
   //boost::shared_ptr<Base> b(boost::static_pointer_cast<Base>(a));
   boost::shared_ptr<A> b(boost::static_pointer_cast<A>(a));
   //boost::shared_ptr<A> b(a);

   cout << std::boolalpha << a.unique() << endl;
   cout << std::boolalpha << b.unique() << endl;

   return 0;
}
