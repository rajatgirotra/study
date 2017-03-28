/*

   "Removing" Elements
   The remove() algorithm removes elements from a range. However, if you use it for all elements
   of a container it operates in a surprising way. Consider the following example:
 */

// stl/remove1.cpp
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
   cout << "pre: ";
   copy (coll.begin(), coll.end(), //source
         ostream_iterator<int> (cout," ")); //destination
   cout << endl;
   //remove all elements with value 3
   remove (coll.begin() , coll.end(), //range
         3); //value
   //print all elements of the collection
   cout << "post: ";
   copy (coll.begin(), coll.end(), //source
         ostream_iterator<int> (cout," ")); //destination
   cout << endl;
   cout << coll.size();
}

/*
the output of the program is as follows:
pre: 6 5 4 3 2 1 1 2 3 4 5 6
post: 6 5 4 2 1 1 2 4 5 6 5 6
Thus, remove() did not change the number of elements in the collection for which it was called.
The end() member function returns the old end, whereas size() returns the old number of
elements. However, something has changed: The elements changed their order as if the
elements were removed. Each element with value 3 was overwritten by the following elements
(Figure 5.7). At the end of the collection, the old elements that were not overwritten by the
algorithm remain unchanged. Logically, these elements no longer belong to the collection.

However, the algorithm does return the new end. By using it, you can access the resulting range,
reduce the size of the collection, or process the number of removed elements.
*/
