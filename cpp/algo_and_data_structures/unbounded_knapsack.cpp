/* unbounded knapsack problem */

#include <iostream>
#include <vector>
#include <set>
#include <utility>
#include <array>
#include <algorithm>
using namespace std;
using ValueWeightList_t = vector<pair<int, int>>;

// example 1
//constexpr int W = 20;

// example 2
//constexpr int W = 20;

// example 3
constexpr int W = 8;

int knapsack(const ValueWeightList_t& input) {
    std::array<int, W+1> m{};
    for(int w = 1; w <= W; ++w) {
        auto max_value = 0;
        for (const auto& item : input) {
            auto value = item.first;
            auto weight = item.second;
            if (weight > w) {
                m[w] = std::max(m[w], m[w-1]);
            } else {
                max_value = std::max(m[w-weight] + value, m[w-1]); 
                if (max_value > m[w]) {
                    m[w] = max_value;
                }
            }
        } 
        cout << "m[" << w << "]: " << m[w] << endl;
    }
    return m[W];
}

int main() {
    ValueWeightList_t valueWeightList;
    /*valueWeightList.push_back(std::make_pair(90,5));
    valueWeightList.push_back(std::make_pair(350,15));
    valueWeightList.push_back(std::make_pair(390,20)); */

    // example 2
  /*   valueWeightList.push_back(std::make_pair(50,2));
    valueWeightList.push_back(std::make_pair(100,3));
    valueWeightList.push_back(std::make_pair(140,5)); */

    // example 3
    valueWeightList.push_back(std::make_pair(10,1));
    valueWeightList.push_back(std::make_pair(40,3));
    valueWeightList.push_back(std::make_pair(50,4));
    valueWeightList.push_back(std::make_pair(70,5));
    cout << knapsack(valueWeightList) << endl;
    return 0;
}
