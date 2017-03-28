/* Implementing map container */

#include <iostream>
#include <map>
#include <string>
using namespace std;

int main()
{
string names[] = { "ABC", "XYZ", "PQR", "UVW", "LMN" };
int pops[] = { 2, 3, 4, 5, 6 };

int pop;
string name;
int i;

map<string, int, less<string> >mapStates;

for(i = 0; i < 5; ++i)
{
name = names[i];
pop = pops[i];

mapStates[name] = pop;
}

map<string, int, less<string> >::iterator iter;

iter = mapStates.begin();

while(iter != mapStates.end())
{ cout<<(*iter).first<<" " <<(*iter).second<<" "<<endl;
  iter++;
}

return 0;
}

/*

The class Map is defined as:

template <class Key, class T, class Compare = less<Key>, class Allocator = allocator<pair<const Key, T> > >
class map
{
...
};

The first template parameter is the Key, the second is the Value, the third is a function object, i.e. a template class "less" whose which overloads the function call operator.

*/
