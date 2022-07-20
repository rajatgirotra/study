/*
Write a program to find the smallest positive integer missing in an unsorted array of integers.
Example: [3, -3, 6, 1]
And: 2

Solution: 
Brute Force: Start with 1 and search it in the array
Then search 2 in the array, then 3, then 4 and so on..
This will be O(nk), where k is the missing positive integer.

Better solution: Sort it in O(n lgn) time and then search for 1, 2, 3, 4, and so on.
This will be O(n lg n)

Hash Set: Create a hash set of all positive integers (>0) in the array. That will be O(n) time
and O(n) space. Then again start search from 1, and then 2, 3, etc in the hash set which will be O(n) also.
So overall O(n) space and O(n) time.

Then there is another neat way which will be O(n) time and O(1) space. In that solution, we basically
re-use the input array to work as our hash-set. Lets see how.

For an input array of size n? what could be the possible set of answers?? It would be
always [1..n+1]. Example for input size 5: [1, 2, 3, 4, 5], answer is 6.
For any other input arr of size 5, the answer will always lie between 1 and 6 only.
So basically we need to just remember if element 1 is in the input array or not, element 2 is in the input array..
like that upto element 5. So we need to remember 5 things and we can use our input array of size 5 for that.
This will we can tell in constant time O(1) if a value exists in the input array.
So to tell if 2 exists, we have to go to index 2-1 = index 1 and check the value there.
Basically if a value 2 exists, we actually go to index 2-1 = index 1 and change that value to a negative to indicate its presence.

So element at index 0 will remember if 1 was present, element at index 1 will remember if 2 was present in input or not.

How do we do this?

[3, -3, 6, 3]
[3, 0, 6, 3] --> change all negatives to 0 as they are useless.
for i in range(len(arr)):
   idx = abs(arr[value]) - 1
   if idx is inside the array bounds:
       change arr[idx] to a negative value
       // take precaution if the number is already negative. Also if number is 0, change it to -(len(arr) + 1)

finally iterate over 1..4
   idx = i - 1
   if arr[idx] < 0: 
      It appears.
    if arr[idx] > 0:
       return idx
*/
#include <iostream>
#include <algorithm>
#include <random>
#include <iterator>
#include <array>
#include <cmath>
using namespace std;

template <size_t N>
void smallest_missing_positive_integer(std::array<int, N>& arr) {
    // first change all negatives values to 0
    for(auto&& val : arr) {
        val = std::max(0, val);
    }

    for(size_t idx = 0; idx < N; ++idx) {
        auto val = abs(arr[idx]) - 1;

        // if val is within the bounds of the array, change the value at arr[val] to negative
        if (val >= 0 and val < N) {
            if (arr[val] == 0) {
                arr[val] = -1 * (N+1);
            } else {
                arr[val] = std::min(arr[val], arr[val] * -1);
            }
        }
    }

//    std::copy(begin(arr), end(arr), std::ostream_iterator<int>(cout, "  "));
    // finally iterate one last time
    size_t idx {};
    for(idx = 1; idx <= N; ++idx) {
        if(arr[idx - 1] >= 0) {
            cout << "smallest missing positive integer: " << idx << endl;
            return;
        }
    }
    
    cout << "smallest missing positive integer: " << idx << endl;
}

int main() {
    // std::array<int, 3> arr {1, 2, 0};
    std::array<int, 4> arr {3, 4, -1, -1};
    cout << "Input array: ";
    std::copy(begin(arr), end(arr), std::ostream_iterator<int>(cout, "  "));
    cout << endl;
    smallest_missing_positive_integer(arr);
}
