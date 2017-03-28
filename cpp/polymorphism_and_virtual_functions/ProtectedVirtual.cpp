/*
Please read Virtuality first
This is an example of guide line 3
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

protected:
   virtual int doMoreFoo()
   {
      cout<<"inside Widget::doMoreFoo()"<<endl;
      return 1;
   }
};

class Textbox : public Widget
{
private:
   int doMoreFoo()
   {
      cout<<"inside Textbox::doMoreFoo()"<<endl;
      Widget::doMoreFoo();
      return 2;
   }
};

int main()
{
   Widget* poW = new Textbox();
   cout<<poW->foo()<<endl;
   delete poW;
   return 0;
}

