#include <iostream>
#include <set>
#include <algorithm>
#include <iterator>
using namespace std;
int main()
{
set<int> coll;
//insert elements from 1 to 9
for (int i=1; i<=9; ++i) {
coll.insert(i);
}
//print all elements of the collection
copy (coll.begin(), coll.end(),
ostream_iterator<int>(cout," "));
cout << endl;
/*Remove all elements with value 3
* - algorithm remove() does not work
* - instead member function erase() works
*/
int num = coll.erase(3);
//print number of removed elements
cout << "number of removed elements: " << num << endl;
//print all elements of the modified collection
copy (coll.begin(), coll.end(),
ostream_iterator<int>(cout," "));
cout << endl;
}
/*
Note that containers provide different erase() member functions. Only the form that gets the
value of the element(s) to remove as a single argument returns the number of removed elements.
Of course, when duplicates are not allowed, the return value can only be 0 or 1 (as is the case for
sets and maps).
The output of the program is as follows:
1 2 3 4 5 6 7 8 9
number of removed elements: 1
1 2 4 5 6 7 8 9
*/
