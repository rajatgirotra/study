/* See how the Insert iterators work */
#include <iostream>
#include <set>
#include <list>
#include <vector>
#include <deque>
#include <algorithm>
using namespace std;

int main()
{
   list<int> coll1;
   int i;
   for(i = 0; i < 9; ++i)
      coll1.push_back(i);

   /* Use back_insertor with vectors */
   vector<int> coll2;
   copy(coll1.begin(), coll1.end(), back_inserter(coll2));

   for(auto iter = coll2.cbegin(); iter != coll2.cend(); ++iter)
     cout<<*iter<<endl;

   /* Use front_inserter with deques */
   deque<int> coll3;
   copy(coll1.begin(), coll1.end(), front_inserter(coll3));

   for(auto iter = coll3.cbegin(); iter != coll3.cend(); ++iter)
     cout<<*iter<<endl;
  
   /* Use inserter with set's. Only inserter that works for associative container's */
   set<int, greater<int> > coll4;
   copy(coll1.begin(), coll1.end(), inserter(coll4, coll4.begin()));
   for(auto iter = coll4.cbegin(); iter != coll4.cend(); ++iter)
    cout<<*iter<<endl;
   
  
   return 0;
} 
