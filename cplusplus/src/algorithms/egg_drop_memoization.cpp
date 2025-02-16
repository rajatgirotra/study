/*
You are given k identical eggs and you have access to a building with n floors labeled from 1 to n.
You know that there exists a floor f where 0 <= f <= n such that any egg dropped at a floor higher than f will break, and any egg dropped at or below floor f will not break.
Each move, you may take an unbroken egg and drop it from any floor x (where 1 <= x <= n). If the egg breaks, you can no longer use it. However, if the egg does not break, you may reuse it in future moves.
Return the minimum number of moves that you need to determine with certainty what the value of f is.
 */

#include <iostream>
#include <vector>
#include <limits>
using namespace std;

class Solution {
public:
    int eggDrop(int k, int n, std::vector<std::vector<int>>& dp) {
        // base case
        if (k == 1) {return n;}
        if (n == 1 || n == 0) {return n;}

        int low = 1; int high = n;
        int minAttempts = std::numeric_limits<int>::max();
        while (low <= high) {
            int mid = (low+high)/2;

            int breakCase = eggDrop(k-1, mid-1, dp);
            int safeCase = eggDrop(k, n - mid, dp);

            int worstCase = 1 + std::max(breakCase, safeCase);
            minAttempts = std::min(minAttempts, worstCase);

            if (breakCase > safeCase) {
                high = mid-1;
            } else {
                low = mid+1;
            }
        }
        dp[k][n] = minAttempts;
        return minAttempts;
    }

    // k eggs and n floors
    int superEggDrop(int k, int n) {
        // cache for memoization
        std::vector<std::vector<int>> dp(k+1, std::vector<int>(n+1, -1));
        return eggDrop(k, n, dp);
    }


};

int main() {
    Solution s;
    cout << s.superEggDrop(1, 2) << endl;
    cout << s.superEggDrop(2, 6) << endl;
    cout << s.superEggDrop(3, 14) << endl;
}
