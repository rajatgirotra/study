/*

This program shall prove that dynamic_cast<>() returns NULL if it is not a safe downcast 

*/

//: C08:CheckedCast2.cpp
// Uses RTTIs dynamic_cast.
#include <vector>
//#include "../purge.h"
#include "Security.h"
using namespace std;
 
int main() {
  vector<Security*> portfolio;
  portfolio.push_back(new Metal);
  portfolio.push_back(new Investment);
  portfolio.push_back(new Bond);
  portfolio.push_back(new Stock);
  for(vector<Security*>::iterator it =
       portfolio.begin();
       it != portfolio.end(); ++it) {
    Investment* cm = dynamic_cast<Investment*>(*it);
    if(cm)
      cm->special();
    else
      cout << "not a Investment" << endl;
  }
  cout << "cast from intermediate pointer: "<< endl;
  Security* sp = new Metal;
  Investment* cp = dynamic_cast<Investment*>(sp);
  if(cp) { cout << "  it's an Investment "<< endl;  cp->special(); }
  Metal* mp = dynamic_cast<Metal*>(sp);
  if(mp) { cout << "  it's a Metal too! "<< endl; mp->special(); }
//  purge(portfolio);
} ///:~

/* 

This example is much shorter, since most of the code in the original example was just the overhead for checking the casts. The target type of a dynamic_cast is placed in angle brackets, like the other new-style C++ casts (static_cast, and so on), and the object to cast appears as the operand. dynamic_cast requires that the types you use it with be polymorphic if you want safe downcasts.[118] This in turn requires that the class must have at least one virtual function. Fortunately, the Security base class has a virtual destructor, so we didnt have to invent an extra function to get the job done. Because dynamic_cast does its work at runtime, using the virtual table, it tends to be more expensive than the other new-style casts.

*/
