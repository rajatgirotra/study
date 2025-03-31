#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <iterator>
using namespace std;

int getMaxCoins([[maybe_unused]] int initialEnergy, const vector<int>& energy, const vector<int>& coins) {
    int n = energy.size();
    std::vector<std::vector<int>> dp(n+1, std::vector<int>(n+1, -1));

    dp[0][initialEnergy] = 0;

    for (int i = 0; i < n; ++i) { // visiting each house
        for (int e = 0; e <= n; ++e) {
            if (dp[i][e] == -1) continue; // will never reach here.

            // Note that house i is actually at index i+1 in the dp array. take energy at this house i.
            // which means number of coins at [i+1][newEnergy] will be
            // either same as dp[i][e] or dp[i+1][newEnergy] whichever is maximum.
            int newEnergy = e + energy[i];
            dp[i+1][newEnergy] = max(dp[i+1][newEnergy], dp[i][e]);

            // take coins, only if energy is > 0
            if (e > 0) {
                dp[i+1][e-1] = max(dp[i+1][e-1], dp[i][e] + coins[i]);
            }
        }
    }
    cout << "Final dp table: \n";
    for (int i = 0; i <= n; ++i) {
        // visiting each house
        for (int e = 0; e <= n; ++e) {
            cout << std::setw(4) << dp[i][e];
        }
        cout << endl;
    }

    return *std::max_element(dp[n].begin(), dp[n].end());
}

int main() {
    // std::vector<int> energy {2, 1, 1};
    // std::vector<int> coins {1, 5, 7};
    // int initialEnergy = 0;

    std::vector<int> energy {1, 1};
    std::vector<int> coins {5, 5};
    int initialEnergy = 0;

    // std::vector<int> energy {1, 1, 1, 1};
    // std::vector<int> coins {4, 3, 2, 1};
    // int initialEnergy = 2;

    auto result = getMaxCoins(initialEnergy, energy, coins);
    cout << "Max coins: " << result << endl;

    return 0;

}