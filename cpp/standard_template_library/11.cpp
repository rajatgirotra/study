/* What hapens if destination container is not big enough */
#include <iostream>
#include <algorithm>
#include <list>
#include <vector>
#include <deque>
using namespace std;

int main()
{
   list<int> coll1;
   vector<int> coll2;
   int i = 0;

   for(i = 0; i < 9; ++i)
   coll1.push_back(i);

   /* Resize coll2 */
   coll2.resize(coll1.size());
   //coll2.reserve(100);

   copy(coll1.begin(), coll1.end(), coll2.begin());

   for(vector<int>::iterator iter = coll2.begin(); iter != coll2.end(); ++iter)
   {
      cout<<*iter<<endl;
   }

   return 0;
} 

/*
 * Ideally always prefer to use range based constructor or range based assign member function. They are more optimized
 * than std::copy()
 */

