/*
 * You have planned some train traveling one year in advance. The days of the year in which you will travel are given as an integer array days. Each day is an integer from 1 to 365.

 Train tickets are sold in three different ways:

 a 1-day pass is sold for costs[0] dollars,
 a 7-day pass is sold for costs[1] dollars, and
 a 30-day pass is sold for costs[2] dollars.
 The passes allow that many days of consecutive travel.

 For example, if we get a 7-day pass on day 2, then we can travel for 7 days: 2, 3, 4, 5, 6, 7, and 8.
 Return the minimum number of dollars you need to travel every day in the given list of days.
 */

#include <iostream>
#include <algorithm>
#include <limits>
#include <array>
#include <unordered_map>
using namespace std;

template <size_t N_DAYS, size_t N_COSTS>
int min_cost_helper(const std::array<size_t, N_DAYS>& days, const std::array<size_t, N_COSTS>& costs, size_t days_idx) {
    // cout << "min_cost_helper(" << days_idx << ") called\n";
    static std::unordered_map<size_t, size_t> costMap {};

    if (days_idx >= days.size()) {
        return 0;
    } else {
        auto iter = costMap.find(days_idx);
        if (iter != costMap.end()) {
            return iter->second;
        } else {
            static size_t pass_duration[3] {1, 7, 30};
            costMap[days_idx] = std::numeric_limits<size_t>::max();
            for(size_t cost_idx = 0; cost_idx < costs.size(); ++cost_idx) {
                size_t j = days_idx + 1;
                while (j < days.size() && days[j] < days[days_idx] + pass_duration[cost_idx]) {
                    ++j;
                }
                costMap[days_idx] = std::min(costMap[days_idx], costs[cost_idx] + min_cost_helper(days, costs, j));
            }
        }
        return costMap[days_idx];
    }
}

template <size_t N_DAYS, size_t N_COSTS>
int min_cost_of_tickets(const std::array<size_t, N_DAYS>& days, const std::array<size_t, N_COSTS>& costs) {
        return min_cost_helper(days, costs, 0);
}


int main() {
        std::array<size_t, 3> costs {2, 7, 15};
        std::array<size_t, 6> days {1, 4, 6, 7, 8, 20};
        cout << min_cost_of_tickets(days, costs) << endl;
}
