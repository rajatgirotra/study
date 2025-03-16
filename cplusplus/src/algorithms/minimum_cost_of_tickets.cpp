/*
You have planned some train traveling one year in advance. The days of the year in which you will travel are given as an integer array days. Each day is an integer from 1 to 365.

Train tickets are sold in three different ways:

a 1-day pass is sold for costs[0] dollars,
a 7-day pass is sold for costs[1] dollars, and
a 30-day pass is sold for costs[2] dollars.
The passes allow that many days of consecutive travel.

For example, if we get a 7-day pass on day 2, then we can travel for 7 days: 2, 3, 4, 5, 6, 7, and 8.
Return the minimum number of dollars you need to travel every day in the given list of days.

Input: days = [1,4,6,7,8,20], costs = [2,7,15]
Output: 11
*/

#include <array>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <iterator>
#include <random>
#include <vector>
using namespace std;

auto minimum_cost_of_tickets(const vector<int> &days, const vector<int> &costs) {
    vector<int> dp(366, 0);
    for (int day = 1; day <= 365; ++day) {
        auto iter = std::find(begin(days), end(days), day);
        if (iter == end(days)) {
            dp[day] = dp[day - 1];
        } else {
            std::array<int, 3> arr{
                dp[std::max(0, day - 1)] + costs[0],
                dp[std::max(0, day - 7)] + costs[1],
                dp[std::max(0, day - 30)] + costs[2]
            };
            dp[day] = *std::min_element(arr.begin(), arr.end());
        }
    }
    return dp.back();
}

int main() {
    std::random_device rd;
    std::default_random_engine engine(rd());
    std::uniform_int_distribution<int> dist(1, 365);

    auto gen = [&]() { return dist(engine); };

    std::vector<int> days(9, 0);
    for (int i = 0; i < days.size(); ++i) {
        std::generate(begin(days), end(days), gen);
    }

    days.clear();
    days.assign({1,4,6,7,8,20});

    days.clear();
    days.assign({1,2,3,4,5,6,7,8,9,10,30,31});

    std::vector<int> costs{2, 7, 15};

    cout << "days: "; std::copy(begin(days), end(days), ostream_iterator<int>(cout, " "));
    cout << endl;

    auto res = minimum_cost_of_tickets(days, costs);
    cout << "minimum_cost_of_tickets: " << res << endl;
}
