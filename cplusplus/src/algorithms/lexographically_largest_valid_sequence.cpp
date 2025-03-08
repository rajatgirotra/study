/*
https://leetcode.com/problems/construct-the-lexicographically-largest-valid-sequence/description/?envType=daily-question&envId=2025-02-16
Based on backtracking and greedy approach
 */
#include <vector>
#include <algorithm>
#include <iostream>
#include <ranges>

using namespace std;
namespace rng = std::ranges;

class Solution {
public:
    vector<int> constructDistancedSequence(int n) {
        vector<int> result(2 * n - 1, 0); // Initialize the result sequence with zeros
        vector<bool> used(n + 1, false); // Track which numbers have been used
        backtrack(result, used, 0, n);
        return result;
    }

private:
    bool backtrack(vector<int> &result, vector<bool> &used, int index, int n) {
        if (index == result.size()) {
            return true; // If we've filled the sequence, return true
        }

        if (result[index] != 0) {
            return backtrack(result, used, index + 1, n); // If the current position is already filled, move to the next
        }

        // Try placing the largest possible number first to ensure lexicographical order
        for (int num = n; num >= 1; --num) {
            if (used[num]) continue; // Skip if the number is already used

            if (num == 1) {
                result[index] = 1;
                used[1] = true;
                if (backtrack(result, used, index + 1, n)) {
                    return true;
                }
                used[1] = false;
                result[index] = 0;
            } else {
                if (index + num >= result.size() || result[index + num] != 0) {
                    continue; // Skip if the second position for the number is out of bounds or already filled
                }

                result[index] = num;
                result[index + num] = num;
                used[num] = true;

                if (backtrack(result, used, index + 1, n)) {
                    return true;
                }

                used[num] = false;
                result[index] = 0;
                result[index + num] = 0;
            }
        }

        return false; // If no number can be placed, backtrack
    }
};

int main() {
    int n = 5;
    auto res = Solution().constructDistancedSequence(n);
    rng::copy(res, ostream_iterator<int>(cout, " "));
}
