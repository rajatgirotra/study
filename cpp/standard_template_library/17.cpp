/*Predicates

A special kind of auxiliary function for algorithms is a predicate. Predicates are functions that return a Boolean value. They are often used to specify a sorting or a search criterion. Depending on their purpose, predicates are unary or binary. Note that not every unary or binary function that returns a Boolean value is a valid predicate. The STL requires that predicates always yield the same result for the same value. This rules out functions that modify their internal state when they are called. See Section 8.1.4, for details.

Unary Predicates

Unary predicates check a specific property of a single argument. A typical example is a function that is used as a search criterion to find the first prime number:
*/

// stl/prime1.cpp
#include <iostream>
#include <list>
#include <algorithm>
#include <cstdlib> //for abs()
using namespace std;
//predicate, which returns whether an integer is a prime number
bool isPrime (int number)
{
  //ignore negative sign
  number = abs(number);
  // 0 and 1 are prime numbers
  if (number == 0 || number == 1) {
    return true;
  }
  //find divisor that divides without a remainder
  int divisor;
  for (divisor = number/2; number%divisor != 0; --divisor) {
    ;
  }
  //if no divisor greater than 1 is found, it is a prime number
  return divisor == 1;
}
int main()
{
  list<int> coll;
  //insert elements from 24 to 30
  for (int i=24; i<=30; ++i) {
    coll.push_back(i);
  }
  //search for prime number
  list<int>::iterator pos; pos = find_if (coll.begin(), coll.end(), //range
      &isPrime); //predicate
  if (pos != coll.end()) {
    //found
    cout << *pos << " is first prime number found" << endl;
  }
  else {
    //not found
    cout << "no prime number found" << endl;
  }
}

#if 0

In this example, the find_if() algorithm is used to search for the first element of the given range for which the passed unary predicate yields true. Here, the predicate is the isPrime() function. This function checks whether a number is a prime number. By using it, the algorithm returns the first prime number in the given range. If the algorithm does not find any element that matches the predicate, it returns the end of the range (its second argument). This is checked after the call. The collection in this example has a prime number between 24 and 30. So the output of the program is as follows:

29 is first prime number found

Binary Predicates

Binary predicates typically compare a specific property of two arguments. For example, to sort elements according to your own criterion you could provide it as a simple predicate function. This might be necessary because the elements do not provide operator < or because you wish to use a different criterion. The following example sorts elements of a set by the first name and last name of a person:

// stl/sort1.cpp
#include <iostream>
#include <string>
#include <deque>
#include <algorithm>
using namespace std;
class Person {
  public:
    string firstname() const;
    string lastname() const;
    ...
};
/*binary function predicate:
 *- returns whether a person is less than another person
 */
bool personSortCriterion (const Person& p1, const Person& p2)
{
  /*a person is less than another person
   *- if the last name is less
   *- if the last name is equal and the first name is less
   */
  return p1.lastname()<p2.1astname() ||
    (!(p2.1astname()<p1.lastname()) &&
     p1.firstname()<p2.firstname());
}
int main()
{
  deque<Person> coll;
  ...
    sort (coll. begin(), coll. end() , //range
        personSortCriterion); //sort criterion
  ...
}


Note that you can also implement a sorting criterion as a function object. This kind of implementation has the advantage that the criterion is a type, which you could use, for example, to declare sets that use this criterion for sorting its elements. See Section 8.1.1, for such an implementation of this sorting criterion.

#endif

