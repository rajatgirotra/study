/* Same as best_time_to_buy_sell_stock_2.cpp but there is one more restriction.
 * There is a cooling-off period of 1 day after you sell. so if you sell on day T, you can only buy again
 * on day T+2.
 * as always draw an inverted tree and look at the possible paths. The node in the tree should be the maxProfit
 * at each step.
 * build an example for:
 * [1, 2, 3, 0, 2]
 *
 * https://www.youtube.com/watch?v=I7j0F7AHpb8
 */

#include <iostream>
#include <array>
#include <random>
#include <string>
#include <algorithm>
#include <iterator>
#include <optional>
#include <vector>
#include <unordered_map>
#include <utility>
using namespace std;

namespace std {
    template<>
    class hash<std::pair<int, bool>> {
    public:
        size_t operator() (const std::pair<int, bool>& p) const noexcept {
            return std::hash<int>{}(p.first) ^ std::hash<bool>{}(p.second);
        }
    };
}

class Solution {
public:
    int maxProfitUtil(const vector<int>& prices, int index, bool buying,
                      std::unordered_map<std::pair<int, bool>, int>& cache) {
        //base case (is index out of bounds)
        if(index >= prices.size()) {
            return 0;
        } else if (cache.find({index, buying}) != cache.end()) {
            return cache[{index, buying}];
        }
        auto cooldown_profit = maxProfitUtil(prices, index+1, buying, cache);
        if (buying) {
            auto buying_profit = maxProfitUtil(prices, index+1, !buying, cache) - prices[index];
            cache[{index, buying}] = std::max(cooldown_profit, buying_profit);
        } else {
            auto selling_profit = maxProfitUtil(prices, index+2, !buying, cache) + prices[index];
            cache[{index, buying}] = std::max(cooldown_profit, selling_profit);
        }
        return cache[{index, buying}];
    }

    int maxProfit(vector<int>& prices) {
        std::unordered_map<std::pair<int, bool>, int> cache{};
        return maxProfitUtil(prices, 0, true, cache);
    }
};

int main() {
    std::random_device rd;
    std::default_random_engine engine(rd());
    std::uniform_int_distribution<size_t> dist(10, 90);
    [[maybe_unused]] auto gen = [&dist, &engine] () { return dist(engine);};

//    std::vector<int> stock_prices(5);
//    std::generate(begin(stock_prices), end(stock_prices), gen);

    std::vector<int> stock_prices{48,12,60,93,97,42,25,64,17,56,85,93,9,48,52,42,58,85,81,84,69,36,1,54,23,15,72,15,11,94};

    cout << "Stock prices: ";
    std::copy(begin(stock_prices), end(stock_prices), std::ostream_iterator<size_t> (cout, ", "));

    cout << endl;
    Solution s;
    auto maxProfit = s.maxProfit(stock_prices);
    cout << "Max profit: " << maxProfit << "\n";
}