/* Using auto_ptr myself */
#include <iostream>
#include <memory>
#include <cstdlib>
using namespace std;

class Foo
{
unsigned int i;
char* data;

public:
   Foo(unsigned int arg = 10) : i(arg)
   {
      cout<<"Foo c'tor running"<<endl;
      data = new char[i];
   }

   ~Foo()
   {
      cout<<"Foo d'tor running"<<endl;
      delete[] data;
   }

   #if 0
   Foo& operator*()
   {
      cout<<"operator * () called"<<endl;
      return *this;
   }
   #endif

   friend ostream& operator << (ostream& os, const Foo& roFoo)
   {
      cout<<"Friend called"<<endl;
      os << roFoo.i<<endl;
   }

   unsigned int operator * ()
   {
      cout<<"operator * () called"<<endl;
      return i;
   }

};

int main()
{
auto_ptr<Foo> poFoo(new Foo(20));

cout<<*poFoo<<endl;

cout<<**poFoo<<endl; //Remember; operator *() works on an *poFoo not on poFoo;

Foo obj(40);
cout<<*obj<<endl;

return 0;
}
 
   
