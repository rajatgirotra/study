#include <iostream>
#include <cstddef>
using namespace std;

class ProxyBase
{
public:
   virtual void f() = 0;
   virtual void g() = 0;
   virtual void h() = 0;
};

class Implementation : public ProxyBase
{
public:
   void f() { cout<<"Implementation::f()"<<endl; }
   void g() { cout<<"Implementation::g()"<<endl; }
   void h() { cout<<"Implementation::h()"<<endl; }
};


class Proxy : public ProxyBase /* This is required */
{
private:

  ProxyBase* poProxyBase;

public:
   Proxy() { poProxyBase = new Implementation(); };
   virtual ~Proxy()
   {
     delete poProxyBase;
   }
   
   void f() { poProxyBase->f(); };
   void g() { poProxyBase->g(); };
   void h() { poProxyBase->h(); };
};

int main()
{
Proxy p;
p.f();
p.g();
p.h();
return 0;
}

/*

Both Proxy and State provide a surrogate class. Your code talks to this surrogate class, and the real class that does the work is hidden behind this surrogate class. When you call a function in the surrogate, it simply turns around and calls the function in the implementing class. These two patterns are so similar that, structurally, Proxy is simply a special case of State. One is tempted to just lump the two together into a pattern called Surrogate, but the intent of the two patterns is different. It can be easy to fall into the trap of thinking that if the structure is the same, the patterns are the same. You must always look to the intent of the pattern in order to be clear about what it does.

The basic idea is simple: from a base class, the surrogate is derived along with the class or classes that provide the actual implementation:

*/
