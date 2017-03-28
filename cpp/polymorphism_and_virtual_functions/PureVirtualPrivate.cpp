/*
Please read Virtuality first
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
   virtual int doMoreFoo() = 0;
};

int Widget::doMoreFoo()
{
   cout<<"Inside Widget::doMoreFoo()"<<endl;
   return 1;
}


class Textbox : public Widget
{
private:
   int doMoreFoo()
   {
      return Widget::doMoreFoo();
   }
};

int main()
{
   Widget* poW = new Textbox();
   cout<<poW->foo()<<endl;
   delete poW;
   return 0;
}

