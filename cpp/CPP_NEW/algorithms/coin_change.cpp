/*
 * You are given an integer array coins representing coins of different denominations and an integer amount representing a total amount of money.
Return the fewest number of coins that you need to make up that amount. If that amount of money cannot be made up by any combination of the coins, return -1.
You may assume that you have an infinite number of each kind of coin.
*/

#include <iostream>
#include <array>
#include <algorithm>
using namespace std;

template <size_t N>
int coin_change(const std::array<int, N>& coins, int amount) {
    std::vector<int> dp(amount + 1, amount+1);
    dp[0] = 0;
    for(auto i = 1; i <= amount; ++i) {
        for(auto c = 0; c < coins.size(); ++c) {
            if(coins[c] > i) {
                continue;
            }
            dp[i] = std::min(dp[i], 1 + dp[i-coins[c]]);
        }
    }

    return (dp[amount] == amount+1 ? -1 : dp[amount]);
}

int main() {
    std::array<int, 4> coins {1, 3, 4, 5};

    cout << coin_change(coins, 7) << endl;
}