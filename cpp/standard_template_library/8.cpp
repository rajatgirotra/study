#include <iostream>
#include <set>

using namespace std;

int main()
{
   //typedef set<int> Intset;
   //typedef set<int, greater<int> > Intset;
   typedef multiset<int, greater<int> > Intset;
   //typedef multiset<int> Intset;

   Intset coll;
   coll.insert(4);
   coll.insert(1);
   coll.insert(5);
   coll.insert(6);
   coll.insert(4);
   coll.insert(1);
   coll.insert(5);

   Intset::const_iterator p;

   for(p = coll.begin(); p != coll.end(); ++p)
      cout<<*p<<endl;

   return 0;
}

