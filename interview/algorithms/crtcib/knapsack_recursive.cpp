/*
Knapsack recursive
*/
#include <iostream>
#include <array>
#include <unordered_map>
#include <limits>
#include <vector>
#include <set>
#include <cmath>
using namespace std;

struct Key {
    int m_items{};
    int m_weight{};

    Key(const int& n, const int& w) : m_items(n), m_weight(w) {}

    auto operator <=> (const Key&) const noexcept = default;
};

namespace std {
    template<>
    struct hash<Key> {
        std::size_t operator () (const Key& k) const noexcept {
            return std::hash<int>{}(k.m_items) ^ std::hash<int>{}(k.m_weight);
        };
    };
}

template <size_t N>
auto ksrecursive(const std::array<int, N>& weights, const std::array<int, N>& values, std::unordered_map<Key, int>& results, const int WEIGHT, const int ITEMS = N) {
    if(ITEMS == 0 || WEIGHT == 0) {
        // cout << "KS(" << ITEMS << ", " << WEIGHT << "): 0\n";
        return 0;
    }

    Key k(ITEMS, WEIGHT);
    auto iter = results.find(k);
    if(iter != results.end()) {
        return iter->second;
    }
    else if (weights[ITEMS-1] > WEIGHT) {
        auto value = ksrecursive(weights, values, results, WEIGHT, ITEMS-1);
        results[k] = value;
        // cout << "KS(" << ITEMS << ", " << WEIGHT << "): " << value << endl;
        return value;
    }        
    else {
        auto valA = ksrecursive(weights, values, results, WEIGHT, ITEMS-1);
        auto valB = ksrecursive(weights, values, results, WEIGHT-weights[ITEMS-1], ITEMS-1) + values[ITEMS-1];
        auto max = std::max(valA, valB);
        //cout << "KS(" << ITEMS << ", " << WEIGHT << "): " << max << endl;
        results[k] = max;
        return max;
    }
}

int main() {
    std::array<int, 3> weights {10, 20, 30};
    std::array<int, 3> values {60, 100, 120};

    constexpr int WEIGHT = 50;

    std::unordered_map<Key, int> results{};
    ksrecursive(weights, values, results, WEIGHT);
    cout << "Knapsack recursive: " << results[Key(3, WEIGHT)] << endl;
}

