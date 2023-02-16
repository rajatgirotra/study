/*
given an array nums of size n. return the majority element. the majority element is the element that occurs more than n/2 times.
So if n = 10, element occurs atleast 6 or more times
if n = 11, element occurs atleast 6 or more times

you can assume that the array always contains a majority element

Solution: Very trivial: just keep a HashMap to maintain count of every element. This solution would require O(n) time and space complexity.

But there is way to do this in O(1) space.
*/

#include <unordered_map>
#include <iostream>
#include <algorithm>
#include <random>
#include <iterator>

using namespace std;

int main() {
	std::array<int, 9> arr {5, 3, 3, 5, 3, 5, 5, 3, 3};

	cout <<"Input array: ";
	std::copy(begin(arr), end(arr), ostream_iterator<int>(cout, " "));
  cout << endl;

  std::unordered_map<int, int> hm;
  auto max_count = 0;
  auto max_elem = arr[0];
  for(auto&& elem : arr) {
      ++hm[elem];
      if(hm[elem] > max_count) { 
          max_count = hm[elem];
          max_elem = elem;
      }
  }

  cout << "Majority element: " << max_elem << endl;

  //O(1) space solution
  /* since there definitely is a majority element, it occurs more than n/2 times. so we can just maintain a single counter as we traverse elements.
     counter is initially zero. everytime we visit an element which is the same as previous element, we increment our counter, otherwise we decrement it.
     We also remember the element we are visiting. When counter reaches zero, we change the element we are visiting to the current element
  */
   auto count = 1;
   auto elem = arr[0];
   for(auto idx = 1; idx < arr.size(); ++idx) {
       if(arr[idx] == elem) {
           ++count;
       } else {
           --count;
           if(count == 0)
               elem = arr[idx];
       }
   }

  cout << "Majority element: " << elem << endl;
}

