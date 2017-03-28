/* How Stream iterators work */
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>
using namespace std;

int main()
{
   cout<<"Enter strings (one per line, terminate with EOF)"<<endl;
   
   vector<string> coll1;
   
   copy(istream_iterator<string>(cin), istream_iterator<string>(), back_inserter(coll1));

   /* Sort the string vector */
   sort(coll1.begin(), coll1.end());

   /* Show them on the output screen */
   copy(coll1.begin(), coll1.end(), ostream_iterator<string>(cout, "\n"));

   return 0;
}
