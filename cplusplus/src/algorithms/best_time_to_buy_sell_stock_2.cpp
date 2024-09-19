/* Same as best_time_to_buy_sell_stock.cpp but can buy and sell multiple times.
 * If you draw a graph and see, it will be very easy. The way it works is that you need to look at the next item in the array.
 * 1. If the next item in the array is lower, you do not buy at the current (higher) price.
 * 2. But if you are already holding, and the next item is lower, you are at a local maxima. So you sell at the current price.
 * 3. If the next item is higher, and you are not holding anything, then you buy at the current price
 *
 * The other very subtle aspect is that if you instead look the previous item, you can code this up in just two lines.
 * I show both solutions
 */

#include <iostream>
#include <array>
#include <random>
#include <string>
#include <algorithm>
#include <iterator>
#include <optional>
using namespace std;

//template <size_t N>
//auto best_time_to_buy_sell_stock(const std::array<size_t, N>& stock_prices) {
//    size_t current {};
//    auto maxProfit = 0L;
//    std::optional<size_t> buyAt;
//    while(current != N-1) {
//        auto diff = static_cast<long>(stock_prices[current+1] - stock_prices[current]);
//        if (diff <= 0) {
//            if(buyAt.has_value()) {
//                maxProfit += (stock_prices[current] - buyAt.value());
//                buyAt.reset();
//            }
//        } else {
//            // buy or hold
//            if(!buyAt.has_value()) {
//                buyAt = stock_prices[current];
//            }
//        }
//        ++current;
//    }
//    if(buyAt.has_value() && buyAt.value() < stock_prices[N-1]) {
//        maxProfit += (stock_prices[N-1] - buyAt.value());
//    }
//    return maxProfit;
//}

template <size_t N>
auto best_time_to_buy_sell_stock(const std::array<size_t, N>& stock_prices) {
    size_t current {1};
    auto maxProfit = 0L;

    while(current != N) {
        if(stock_prices[current] > stock_prices[current-1]) {
            maxProfit += (stock_prices[current] - stock_prices[current-1]);
        }
        ++current;
    }
    return maxProfit;
}

int main() {
    std::random_device rd;
    std::default_random_engine engine(rd());
    std::uniform_int_distribution<size_t> dist(10, 90);
   [[maybe_unused]] auto gen = [&dist, &engine] () { return dist(engine);};

    std::array<size_t, 5> stock_prices;
    std::generate(begin(stock_prices), end(stock_prices), gen);

    cout << "Stock prices: ";
    std::copy(begin(stock_prices), end(stock_prices), std::ostream_iterator<size_t> (cout, ", "));

    cout << endl;
    auto maxProfit= best_time_to_buy_sell_stock(stock_prices);
    cout << "Maximum profit: " << maxProfit << "\n";
}
