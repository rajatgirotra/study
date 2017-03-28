/*
Please read Virtuality first
This is an example of guide line 2
*/

#include <iostream>
using namespace std;

class Widget
{
public:
   int foo()
   {
      return doMoreFoo();
   }

   virtual ~Widget()
   {
   }

private:
   virtual int doMoreFoo()
   {
      return 1;
   }
};

class Textbox : public Widget
{
private:
   int doMoreFoo()
   {
      cout<<"inside Textbox::doMoreFoo()"<<endl;
      return 2;
   }
};

int main()
{
   Widget* poW = new Textbox();
   cout<<poW->foo()<<endl;
   Textbox tx;
   //tx.doMoreFoo(); //--> Still can't call it directly like this. You need to upcast to A. or call tx.foo() instead.
   tx.foo();
   delete poW;
   return 0;
}

