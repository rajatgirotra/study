/*
 * You are given an integer array coins representing coins of different denominations and an integer amount representing a total amount of money.

Return the fewest number of coins that you need to make up that amount. If that amount of money cannot be made up by any combination of the coins, return -1.

You may assume that you have an infinite number of each kind of coin.
*/

#include <iostream>
#include <array>
#include <algorithm>
using namespace std;

template <size_t N, int amount>
int coin_change(const std::array<int, N>& coins) {
    int dp[amount + 1];
    std::fill(begin(dp), end(dp), amount + 1);

    dp[0] = 0;

    for(auto dp_idx = 1; dp_idx <= amount; ++dp_idx) {
	for(auto idx = 0; idx < coins.size(); ++idx) {
	    auto val = dp_idx - coins[idx];
	    if (val >= 0) {
	        dp[dp_idx] = std::min(dp[dp_idx], 1 + dp[val]);
	    } 
	}
    } 
    if(dp[amount] != amount+1) {
        return dp[amount];
    } else {
        return -1;
    }
}

int main() {
    std::array<int, 4> coins {1, 3, 4, 5};

    cout << coin_change<coins.size(), 7>(coins) << endl;
}
