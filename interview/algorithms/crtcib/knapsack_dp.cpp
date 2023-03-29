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

template <size_t N, size_t W>
auto ksdynamic(const std::array<int, N>& weights, const std::array<int, N>& values) {
    std::array<std::array<int, W+1>, N+1> cells{};

    for(int n = 0; n <= N; ++n) {
        for(int w = 0; w <= W; ++w) {
            if(n == 0 || w == 0) {
                cells[n][w] = 0;
                // cout << "(" << n << ", " << w << ": " << cells[n][w] << endl;
            } else if (weights[n-1] > w) {
                cells[n][w] = cells[n-1][w];
                // cout << "(" << n << ", " << w << ": " << cells[n][w] << endl;
            } else {
                cells[n][w] = std::max(
                                 cells[n-1][w],
                                 cells[n-1][w-weights[n-1]] + values[n-1]);
                // cout << "(" << n << ", " << w << ") C: " << cells[n][w] << endl;
            }
        }
    }

    return cells[N][W];
}

int main() {
    std::array<int, 3> weights {10, 20, 30};
    std::array<int, 3> values {60, 100, 120};
    auto result = ksdynamic<3, 50>(weights, values);
    cout << "Knapsack dynamic: " << result << endl;
}

