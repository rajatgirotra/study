/* How to use for each and transform algorithms */
#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
#include <list>
#include <iterator>
#include "15.h"
using namespace std;

void print(int elem)
{
   cout<<elem<<"  ";
}

int square(int value)
{
   return value*value;
}


int main()
{
   vector<int> objVector;
   int i;
   set<int> coll1;
   list<int> coll2;

   for( i = 1; i < 10; ++i)
      objVector.push_back(i);

   /* for_each() algorithm */
   for_each(objVector.begin(), objVector.end(), &print); 

   cout<<endl;

   for( i = 1; i < 10; ++i)
      coll1.insert(i);
   
   /* transform algorithm */
   transform(coll1.begin(), coll1.end(), front_inserter(coll2), &square);

   copy(coll2.begin(), coll2.end(), ostream_iterator<int>(cout, "  "));

   return 0;
}
