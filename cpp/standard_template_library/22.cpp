/*
   To increase their flexibility and power, several algorithms allow the passing of user-defined
   auxiliary functions. These functions are called internally by the algorithms.

   The simplest example is the for_each() algorithm. It calls a user-defined function for each
   element of the specified range. Consider the following example:
 */

// stl/foreach1.cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;
//function that prints the passed argument
void print (int elem)
{
  cout << elem << ' ' ;
}
int main()
{
  vector<int> coll;
  //insert elements from 1 to 9
  for (int i=1; i<=9; ++i) {
    coll.push_back(i);
  }
  //print all elements
  for_each (coll.begin(), coll.end(), //range
      &print); //operation
  cout << endl;
}

/*

   The for_each() algorithm calls the passed print() function for every element in the range
   [coll.begin(),coll.end()). Thus, the output of the program is as follows:
   1 2 3 4 5 6 7 8 9

 */
