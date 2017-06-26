/* You are given two api's
1) add() to add an item in a list
2) find(sum) to find a pair of indices in the above list such that the sum equals the given sum
The design really depends on the frequency of the add() and find() operations.

1) If find() is too much frequent, compared to add(), then we should look for an O(1) solution.
For every item added to the list, run through the entire list and maintain a hash table of 
<sum, index_pair> for every possible pair.
add(): complexity is O(n)
find(): complexity is O(1)
space complexity is: O(n2) for storing the sum of every pair.

2) If add() is too frequent than find(), then maintain a hash table
add(): will be O(1)
find(): will be O(n). Iterate through the hash table, and do a lookup O(n).
space complexity is O(n) for the hash table.

3) If add() and find() are both common, then maintain a sorted list.
add() will be O(lgn): 
find() will be O(n), based on using two pointer solution of moving through the start and end together.
Space complexity will be O(n) for storing the items in a sorted list.A
*/
