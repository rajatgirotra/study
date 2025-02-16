/*
You are climbing a staircase. It takes n steps to reach the top (n >=1).
Each time you can either climb 1 or 2 steps. In how many distinct ways can you climb to the top?

this is a very trivial DP problem. If n = 2, then there are 2 ways to reach the top.
 1) From 0th step to 2nd step directly.
 2) From 0th step to 1st step and then to 2nd step.

 If n = 3, then there are 3 ways to reach the top.
 1) From 0th step to 2nd step directly and then to 3rd step.
 2) From 0th step to 1st step and then to 3rd step.
 3) From 0th step to 1st step and then to 2nd step and then to 3rd step.
 As you reach the top step n, you increment by 1, the count of ways to reach the top.
 If you overshoot the top step, then you just ignore. Along the way, you cache the count of ways to reach the ith step.
 So basically: dp(n) = dp(n+1) + dp(n+2).
 Without memoization, the runtime would be exponential. With memoization, it is linear.
 Reason: without memoization, it would take time 2 to the power n:
 (2 because in the decision tree, at each step, you have 2 choices. and n because that is the max depth of the decision tree).

 With memoization, the subproblem results are cached, so will only visit each stair once.

 However, there is another way to solve this problem. You can use the fibonacci series to solve this problem. Why? because
 if you see the possible values for n = 5, you will see a fibonacci series. We implement that too here.
*/
#include <iostream>
#include <random>
#include <array>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>
#include <cassert>
#include <memory>
#include <concepts>
#include <type_traits>
#include <ranges>
#include <unordered_map>
#include <utility>

using namespace std;
namespace rng = std::ranges;
namespace vws = std::views;

size_t climbing_stairs_1_helper(int n, int k, std::unordered_map<int, size_t>& countMap) {
    if(k > n) {
        return 0;
    }
    if (k == n) {
        return 1;
    }
    auto iter = countMap.find(k);
    if(iter != countMap.end()) {
        return iter->second;
    }
    auto count = climbing_stairs_1_helper(n, k+1, countMap) + climbing_stairs_1_helper(n, k+2, countMap);
    countMap[k] = count;
    return count;
}

size_t climbing_stairs_1(int n) {
    std::unordered_map<int, size_t> countMap{};
    return climbing_stairs_1_helper(n, 0, countMap);
}

size_t climbing_stairs_fibonacci(int n) {
    assert(n > 0);
    size_t res{1};
    auto gen = [i = 1, j = 2] () mutable {
        i = std::exchange(j, i+j);
        return i;
    };
    for(int i = 0; i < n-1; ++i) {
        res = gen();
    }
    return res;
}

int main() {
    int n = 45;
    cout << "number of ways: " << climbing_stairs_1(n) << endl;
    cout << "number of ways: " << climbing_stairs_fibonacci(n) << endl;
}