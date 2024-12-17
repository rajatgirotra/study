/* Given an array of positive integers find the best time to buy and sell stock to maximize profit.
 * You have to buy before you sell. So you can't sell before you buy.
 * Example:
 *  Stock prices: 10, 20, 30, 5, 10, 15
 *  Buy at: 10 Sell at: 30 for maximum profit of: 20
 *
 *  Can only buy and sell once.
 */

#include <iostream>
#include <array>
#include <random>
#include <string>
#include <algorithm>
#include <iterator>
using namespace std;

// use a two pointer approach.
template <size_t N>
auto best_time_to_buy_sell_stock(const std::array<size_t, N>& stock_prices) {
    size_t l = 0;
    auto r = l+1;
    auto maxProfit = 0L;
    auto buyAt = -1, sellAt = -1;
    while (r != N) {
        if(stock_prices[l] < stock_prices[r]) {
            auto profit = stock_prices[r] - stock_prices[l];
            if(profit > maxProfit) {
                maxProfit = profit;
                buyAt = l;
                sellAt = r;
            }
        } else {
            l = r;
        }
        ++r;
    }
    return std::make_pair(buyAt, sellAt);
}



int main() {
    std::random_device rd;
    std::default_random_engine engine(rd());
    std::uniform_int_distribution<size_t> dist(10, 90);
    auto gen = [&dist, &engine] () { return dist(engine);};

    std::array<size_t, 8> stock_prices;
    std::generate(begin(stock_prices), end(stock_prices), gen);

    cout << "Stock prices: ";
    std::copy(begin(stock_prices), end(stock_prices), std::ostream_iterator<size_t> (cout, ", "));

    cout << endl;
    auto [buyIndex, sellIndex] = best_time_to_buy_sell_stock(stock_prices);
    if(buyIndex == -1 || sellIndex == -1) {
        cout << "No profit can be made\n";
        return 0;
    }
    cout << "Buy at: " << stock_prices[buyIndex] << " Sell at: " << stock_prices[sellIndex]
    << " for maximum profit of: " << stock_prices[sellIndex] - stock_prices[buyIndex] << "\n";
}
