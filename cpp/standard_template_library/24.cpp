// Show the different ways in which the sort algorithm can be used.
// 1. using sort (start, end)
// 2. using sort (start, end, binary-predicate)
// 3. using sort (start, end, object-of-a-class)

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
using namespace std;

struct myclass
{
public:
    bool operator() (int i, int j)
    {
       return (i < j);
    }
}myobject;

bool binary_predicate(int i, int j)
{
   return (i < j);
}

int main()
{
   int myints[] = {23, 56, 0, -432, 32, -21, 99, 0 };
   int i = 0;
   vector<int> myvector(myints, myints + sizeof(myints)/sizeof(myints[0]));

   vector<int>::const_iterator it;
  
   //Sort & print the first 4 elements 
   sort(myvector.begin(), myvector.begin() + 4); 
   cout<<"Using default Sort: ";
   for(it = myvector.begin(); it != myvector.end(); ++it)
      cout<<*it<<" ";
   cout<<endl;

   //Sort & print the last 4 elements; use binary-predicate 
   sort(myvector.begin() + 4, myvector.end(), &binary_predicate); 
   cout<<"Using binary-predicate: ";
   for(it = myvector.begin(); it != myvector.end(); ++it)
      cout<<*it<<" ";
   cout<<endl;

    
   //Sort & print the whole vector now; use function object 
   sort(myvector.begin(), myvector.end(), myobject); 
   cout<<"Using function-object: ";
   for(it = myvector.begin(); it != myvector.end(); ++it)
      cout<<*it<<" ";
   cout<<endl;

   return 0;
}
