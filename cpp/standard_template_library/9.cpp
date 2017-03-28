/* MultiMap Demonstration */
#include <iostream>
#include <map>
#include <string>
#include <memory>
using namespace std;

int main()
{
   typedef multimap<int, string> MultiMap;
   MultiMap mmap;
   
   mmap.insert(make_pair(5, "tagged"));
   mmap.insert(make_pair(1, "This"));
   mmap.insert(make_pair(4, "of"));
   mmap.insert(make_pair(2, "a"));
   mmap.insert(make_pair(3, "multimap"));
   mmap.insert(make_pair(2, "is"));
   mmap.insert(make_pair(5, "strings"));

   MultiMap::iterator iter;
   for(iter = mmap.begin(); iter != mmap.end(); ++iter)
   { 
      cout<<iter->second<<" ";
   }

   cout<<endl;
   return 0;
}

