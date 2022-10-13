/*
Given an array of size n of positive integers which are stock prices over n days, find the maximum profit
that you could earn. You must buy first and then sell later.

Brute Force: O(n^2). for every element, traverse all the values after it to find the minimum and compute the profit.
Then return the max profit.

Better way: Two pointer approach that will be O(n). Left and right pointers; i.e. l and r.
l will be pointing to the buy price and r will point to the sell price.
Very trivial. Initially l = index 0 and r = index 1
then if *l > *r, ie. buy price is higher, we increment both l and r 
otherwise while *l < *r, we compute the profit and keep record of the max profit.
If stop the while loop when *l > *r, and set l = r and r = r+1. think in your mind.
all values between l and r are higher than l, so new l must be r.
*/
#include <iostream>
#include <algorithm>
#include <random>
#include <iterator>
#include <limits>
#include <iomanip>
#include <cstring>
#include <utility>
#include <ctime>
#include <array>
#include <deque>
#include <cassert>
using namespace std;

template<size_t N>
int stock_price_max_profit(std::array<int, N> arr) {
    static_assert(arr.size() > 1);
    auto l = arr.begin();
    auto r = std::next(arr.begin(), 1);
    int maxProfit {0};
    while (r != arr.end()) {
        if(*l > *r) {
            l = r;   
        } else {
            maxProfit = std::max(maxProfit, *r - *l);
        }
        ++r;
    }
    return maxProfit;
}


int main() {
    std::array<int, 10> arr{};
    std::random_device r;
    std::default_random_engine engine(r());
    std::uniform_int_distribution<int> dist(1, 20);
    auto gen = [dist = dist, engine = engine] () mutable {
        return dist(engine);
    };
    std::generate(begin(arr), end(arr), gen);

    cout << "Elements: ";
    std::copy(begin(arr), end(arr), ostream_iterator<int>(cout, " "));
    cout << endl;

    cout << "Max profit is: " << stock_price_max_profit(arr) << endl;
}
