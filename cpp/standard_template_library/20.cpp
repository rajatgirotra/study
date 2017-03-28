// Read 19.cpp first
// stl/remove2.cpp
#include <iostream>
#include <list>
#include <algorithm>
#include <iterator>
using namespace std;
int main()
{
  list<int> coll;
  //insert elements from 6 to 1 and 1 to 6
  for (int i=1; i<=6; ++i) {
    coll.push_front(i);
    coll.push_back(i);
  }
  //print all elements of the collection
  copy (coll.begin(), coll.end(),
      ostream_iterator<int>(cout," "));
  cout << endl;
  //remove all elements with value 3
  // - retain new end
  list<int>::iterator end = remove (coll.begin(), coll.end(),
      3);
  //print resulting elements of the collection
  copy (coll.begin(), end,
      ostream_iterator<int>(cout," "));
  cout << endl;
  //print number of resulting elements
  cout << "number of removed elements: "
    << distance(end,coll.end()) << endl;
  //remove "removed'' elements
  coll.erase (end, coll.end());
  //print all elements of the modified collection
  copy (coll.begin(), coll.end(),
      ostream_iterator<int>(cout," "));
  cout << endl;
}

/*
In this version, the return value of remove() is assigned to the iterator end:
list<int>::iterator end = remove (coll.begin(), coll.end(),
3);
This is the new logical end of the modified collection after the elements are "removed." You can
use this return value as the new end for further operations:
copy (coll.begin(), end,
ostream_iterator<int>(cout," "));
Another possibility is to process the number of "removed" elements by processing the distance
between the "logical" and the real ends of the collection:
cout << "number of removed elements: "
<< distance(end,coll.end()) << endl;
Here, a special auxiliary function for iterators, distance(), is used. It returns the distance
between two iterators. If the iterators were random access iterators you could process the
difference directly with operator -. However, the container is a list, so it provides only
bidirectional iterators.

If you really want to remove the "removed" elements, you must call an appropriate member
function of the container. To do this, containers provide the erase() member function, erase()
removes all elements of the range that is specified by its arguments:
coll.erase (end, coll.end());
Here is the output of the whole program:
6 5 4 3 2 1 1 2 3 4 5 6
6 5 4 2 1 1 2 4 5 6
number of removed elements: 2
6 5 4 2 1 1 2 4 5 6
If you really want to remove elements in one statement, you can call the following statement:
coll.erase (remove(coll.begin(),coll.end(),
3),
coll.end());
Why don't algorithms call erase() by themselves? Well, this question highlights the price of the
flexibility of the STL. The STL separates data structures and algorithms by using iterators as the
interface. However, iterators are an abstraction to represent a position in a container. In general,
iterators do not know their containers. Thus, the algorithms, which use the iterators to access the
elements of the container, can't call any member function for it.
This design has important consequences because it allows algorithms to operate on ranges that
are different from "all elements of a container." For example, the range might be a subset of all
elements of a collection. And, it might even be a container that provides no erase() member
function (ordinary arrays are an example of such a container). So, to make algorithms as flexible
as possible, there are good reasons not to require that iterators know their container.

*/
