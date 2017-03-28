#include <iostream>
#include <memory>
#include <utility>
using namespace std;

class ABC
{
private:
   void* poABCdata;

public:
   ABC()
   {
      cout<<"ABC c'tor running"<<endl;
      poABCdata = new char[20];
   }

   ~ABC()
   {
      cout<<"ABC d'tor running"<<endl;
      char* poDeleteData = static_cast<char*>(poABCdata);
      delete[] poDeleteData;
   }
};

void foo(auto_ptr<ABC> p)
{
    auto_ptr<ABC> ptr = p;
   return;
}
   

int main()
{
   auto_ptr<ABC> poABCObject(new ABC());
   cout<<"Inside main after creating poABCObject"<<endl;
   cout<<"before calling function foo"<<endl;
   foo(poABCObject);
   cout<<"after calling function foo"<<endl;
   return 0;
}
  
