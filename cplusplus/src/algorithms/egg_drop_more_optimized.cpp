/*
You are given k identical eggs and you have access to a building with n floors labeled from 1 to n.
You know that there exists a floor f where 0 <= f <= n such that any egg dropped at a floor higher than f will break, and any egg dropped at or below floor f will not break.
Each move, you may take an unbroken egg and drop it from any floor x (where 1 <= x <= n). If the egg breaks, you can no longer use it. However, if the egg does not break, you may reuse it in future moves.
Return the minimum number of moves that you need to determine with certainty what the value of f is.

Understanding the O(KN) DP Solution
Instead of using binary search or brute force searching for every floor, we can optimize the DP approach by tracking the number of floors we can cover in a given number of attempts.
Key Idea
Define dp[m][k] as:

The maximum number of floors we can check with m moves (drops) and k eggs. The recurrence relation is:
dp[m][k] = dp[m−1][k−1] + dp[m−1][k] + 1
dp[m-1][k-1]: If the egg breaks, we check the floors below.
dp[m-1][k]: If the egg does not break, we check the floors above.
+1 accounts for the floor we just dropped from.
 */

#include <iostream>
#include <vector>
#include <limits>
using namespace std;

class Solution {
public:
    // k eggs and n floors
    int superEggDrop(int k, int n) {
        std::vector<std::vector<int>> dp(n+1, std::vector<int>(k+1, 0));
        int moves = 0;
        while(dp[moves][k] < n) {
            ++moves;
            for (int eggs = 1; eggs <= k; ++eggs) {
                dp[moves][eggs] = dp[moves-1][eggs-1] + dp[moves-1][eggs] + 1;
            }
        }
        return moves;
    }

};

int main() {
    Solution s;
    cout << s.superEggDrop(1, 2) << endl;
    cout << s.superEggDrop(2, 6) << endl;
    cout << s.superEggDrop(3, 14) << endl;
}
