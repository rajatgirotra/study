/* Using set asociative container */
#include <iostream>
#include <algorithm>
#include <set>
#include <string>
using namespace std;

int main()
{
string names[] = { 
                   "Rajat", 
                   "Ajay",
                   "Ashish",
                   "Manik",
                   "Vidhu",
                   "Puneet",
                   "Ankit"
                 };

set<string, less<string> >stringSet(names, names + sizeof(names)/sizeof(names[0]));
set<string, less<string> >::iterator iter;

int i;
for (iter = stringSet.begin(); iter != stringSet.end(); ++iter)
   cout<<*iter<<endl;

return 0;
}

/*
The set is declared in the C++ standard library as:

template <class Key, class Compare=less<Key>, class Allocator=allocator<Key> >
class set
{
...
};

The second template parameter is a class that contains a function that takes two parameters of the same time as the Key & returns a bool. eg: bool comp(a, b). Normally this is a class that implements the function call operator.

Or the second parameter while creating a set can also be a function pointer of the same type as above.

Example 1:
---------

struct mycomp
{
   bool operator() (const int& lhs, const int& rhs) const
   {
      return lhs < rhs;
   }
};

set<int, mycomp> myIntSet;

Example 2:
---------
bool funcComp(const int& lhs, const int& rhs)
{
   return (lhs < rhs);
}

bool (*functPtr)(int, int) = funcComp;
set<int, bool(*)(int, int)> newIntSet(funcComp);


Also since we use the "<" operator to make comparisons, you should always overload the "<" operator if you want to create a set of a user-defined class. Actually you'll mostly have to make it a friend function rather, because it will be called from outside the class and without using any objects. i.e.

friend operator < (const MyClass& obj1, const MyClass& obj2);

*/

