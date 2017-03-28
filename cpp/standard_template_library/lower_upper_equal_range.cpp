/*

   lower_bound() and upper_bound() return the first and last position respectively, at which an
   element with the passed value would be inserted. In other words, lower_bound() returns the
   position of the first element that has the same or a greater value than the argument, whereas
   upper_bound() returns the position of the first element with a greater value. equal_range()
   returns both return values of lower_bound() and upper_bound() as a pair (type pair is
   introduced in Section 4.1). Thus, it returns the range of elements that have the same value as
   the argument. If lower_bound() or the first value of equal_range() is equal to
   upper_bound() or the second value of equal_range(), then no elements with the same
   value exist in the set or multiset. Naturally, in a set the range of elements that have the same
   values could contain at most one element.
   The following example shows how to use lower_bound(), upper_bound(), and equal_range()

 */


// cont/set2.cpp
#include <iostream>
#include <set>
using namespace std;
int main ()
{
  set<int> c;
  c.insert(1);
  c.insert(2);
  c.insert(4);
  c.insert(5);
  c.insert(6);
  cout << "lower_bound(3): " << *c.lower_bound(3) << endl;
  cout << "upper_bound(3): " << *c.upper_bound(3) << endl;
  cout << "equal_range(3): " << *c.equal_range(3).first << " "
               << *c.equal_range(3).second << endl;
  cout << endl;
  cout << "lower_bound(5): " << *c.lower_bound(5) << endl;
  cout << "upper_bound(5): " << *c.upper_bound(5) << endl;
  cout << "equal_range(5): " << *c.equal_range(5).first << " "
               << *c.equal_range(5).second << endl;
}

/*

   The output of the program is as follows:

   lower_bound(3): 4
   upper_bound(3): 4
   equal_range(3): 4 4

   lower_bound(5): 5
   upper_bound(5): 6
   equal_range(5): 5 6

   If you use a multiset instead of a set, the program has the same output.

 */
