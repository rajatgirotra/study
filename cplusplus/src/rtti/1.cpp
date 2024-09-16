//: C08:CheckedCast.cpp
// Checks casts at runtime.
#include <iostream>
#include <vector>
#include "../purge.h"
using namespace std;
 
class Security {
protected:
  enum { BASEID = 0 };
public:
  virtual ~Security() {}
  virtual bool isA(int id) { return (id == BASEID); }
};
 
class Stock : public Security {
  typedef Security Super;
protected:
  enum { OFFSET = 1, TYPEID = BASEID + OFFSET };
public:
  bool isA(int id) {
    return id == TYPEID || Super::isA(id);
  }
  static Stock* dynacast(Security* s) {
    return (s->isA(TYPEID)) ? static_cast<Stock*>(s) : 0;
  }
};
 
class Bond : public Security {
  typedef Security Super;
protected:
  enum { OFFSET = 2, TYPEID = BASEID + OFFSET };
public:
  bool isA(int id) {
    return id == TYPEID || Super::isA(id);
  }
  static Bond* dynacast(Security* s) {
    return (s->isA(TYPEID)) ? static_cast<Bond*>(s) : 0;
  }
};
 
class Investment : public Security {
  typedef Security Super;
protected:
  enum { OFFSET = 3, TYPEID = BASEID + OFFSET };
public:
  bool isA(int id) {
    return id == TYPEID || Super::isA(id);
  }
  static Investment* dynacast(Security* s) { cout<<"Investment = "<<TYPEID<<endl;
    return (s->isA(TYPEID)) ?
      static_cast<Investment*>(s) : 0;
  }
  virtual void special() {
    cout << "special Investment function" << endl;
  }
};
 
class Metal : public Investment {
  typedef Investment Super;
protected:
  enum { OFFSET = 4, TYPEID = BASEID + OFFSET };
public:
  bool isA(int id) { cout<<"Rajat = "<<id<<endl;
    return id == TYPEID || Super::isA(id);
  }
  static Metal* dynacast(Security* s) {
    return (s->isA(TYPEID)) ? static_cast<Metal*>(s) : 0;
  }
   void special() {
    cout << "special Metal function" << endl;
  }
};
 
int main() {
  vector<Security*> portfolio;
  portfolio.push_back(new Metal);
  portfolio.push_back(new Investment);
  portfolio.push_back(new Bond);
  portfolio.push_back(new Stock);
  for(vector<Security*>::iterator it = portfolio.begin();
       it != portfolio.end(); ++it) {
    Investment* cm = Investment::dynacast(*it);
    if(cm)
      cm->special();
    else
      cout << "not an Investment" << endl;
  }
  cout << "cast from intermediate pointer:" << endl;
  Security* sp = new Metal;
  Investment* cp = Investment::dynacast(sp);
  if(cp) cout << "  it's an Investment" << endl;
  Metal* mp = Metal::dynacast(sp);
  if(mp) cout << "  it's a Metal too!" << endl;
  purge(portfolio);
} ///:~


