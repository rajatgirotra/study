/* Simple auto_ptr demonstration */
#include <iostream>
#include <memory>
using namespace std;

/* Overload the << operator for auto_ptr's */
template <typename T>
ostream& operator << (ostream& os, const auto_ptr<T>& p)
{
   if(p.get() == 0)
   {
      os<<"NULL";
   }
   else
   {
      os<<*p;
   }
   return os;
}

int main()
{
   auto_ptr<int> p(new int(42));
   auto_ptr<int> q;

   cout<<"After Initialization"<<endl;
   cout<<"*p = "<<p<<endl;
   cout<<"*q = "<<q<<endl;

   q = p;

   cout<<"After assigning auto_ptrs"<<endl;
   cout<<"*p = "<<p<<endl;
   cout<<"*q = "<<q<<endl;

   *q += 13;

   p = q;

   cout<<"After incrementing & re-assignment"<<endl;
   cout<<"*p = "<<p<<endl;
   cout<<"*q = "<<q<<endl;

   auto_ptr<int> r(p);
   cout<<"After copy construction"<<endl;
   cout<<"*p = "<<p<<endl;
   cout<<"*r = "<<r<<endl;
 

   return 0;
}
