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
  list<int>::iterator pos;
  pos = find_if (coll.begin(), coll.end(), //range
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

/*
   In this example, the find_if() algorithm is used to search for the first element of the given
   range for which the passed unary predicate yields true. Here, the predicate is the isPrime()
   function. This function checks whether a number is a prime number. By using it, the algorithm
   returns the first prime number in the given range. If the algorithm does not find any element that
   matches the predicate, it returns the end of the range (its second argument). This is checked after
   the call. The collection in this example has a prime number between 24 and 30. So the output of
   the program is as follows:

   29 is first prime number found
 */
