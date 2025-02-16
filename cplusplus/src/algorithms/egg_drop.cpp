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
    // k eggs and n floors
    int superEggDrop(int k, int n) {
        // k+1 rows for eggs (0..k)
        // n+1 columns for floors (0..n)
        vector<vector<int> > dp(k + 1, vector<int>(n + 1, 0));
        // set the base values
        for (int i = 1; i <= k; i++) {
            dp[i][1] = 1;
        }

        for (int j = 1; j <= n; j++) {
            dp[1][j] = j;
        }

        for (int i = 2; i <= k; ++i) {
            for (int j = 2; j <= n; ++j) {
                dp[i][j] = std::numeric_limits<int>::max();
                for (int x = 1; x<= j; ++x) {
                    auto res = 1 + std::max(dp[i-1][x-1], dp[i][j-x]);
                    dp[i][j] = std::min(dp[i][j], res);
                }
            }
        }
        return dp[k][n];
    }
};

int main() {
    Solution s;
    cout << s.superEggDrop(1, 2) << endl;
    cout << s.superEggDrop(2, 6) << endl;
    cout << s.superEggDrop(3, 14) << endl;
}
