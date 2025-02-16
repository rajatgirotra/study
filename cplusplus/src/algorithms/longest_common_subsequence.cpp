/*
Given two strings text1 and text2, return the length of their longest common subsequence. If there is no common subsequence, return 0.
A subsequence of a string is a new string generated from the original string with some characters (can be none)
deleted without changing the relative order of the remaining characters.

For example, "ace" is a subsequence of "abcde".
A common subsequence of two strings is a subsequence that is common to both strings.

Example 1:
Input: text1 = "abcde", text2 = "ace"
Output: 3
Explanation: The longest common subsequence is "ace" and its length is 3.
Example 2:

Input: text1 = "abc", text2 = "abc"
Output: 3
Explanation: The longest common subsequence is "abc" and its length is 3.
Example 3:

Input: text1 = "abc", text2 = "def"
Output: 0
Explanation: There is no such common subsequence, so the result is 0.
*/

#include <string>
#include <iostream>
#include <vector>
#include <utility>
using namespace std;

class Solution {
public:
    enum struct Direction {
        DIAGNOL,
        LEFT,
        UP
    };

    auto longestCommonSubsequence(const string& text1, const string& text2) {
        // dp vector to store LCS length and a marker used to print the LCS
        int M = text1.size();
        int N = text2.size();
        std::vector<std::vector<std::pair<int, Direction> > > dp(M + 1,
            std::vector<std::pair<int, Direction> >(
                N + 1, {0, Direction::DIAGNOL}));

        for (int i = 1; i <= M; ++i) {
            for (int j = 1; j <= N; ++j) {
                if (text1[i-1] == text2[j-1]) {
                    dp[i][j].first = dp[i-1][j-1].first + 1;
                    dp[i][j].second = Direction::DIAGNOL;
                } else if (dp[i-1][j] > dp[i][j-1]) {
                    dp[i][j].first = dp[i-1][j].first;
                    dp[i][j].second = Direction::UP;

                } else {
                    dp[i][j].first = dp[i][j-1].first;
                    dp[i][j].second = Direction::LEFT;
                }
            }
        }
        return dp;
    }

    void print_lcs(const string& text1, std::vector<std::vector<std::pair<int, Direction>>>&dp, int i, int j) {
        if (i == 0 || j == 0) {
            return;
        }
        if (dp[i][j].second == Direction::DIAGNOL) {
            print_lcs(text1, dp, i-1, j-1);
            cout << text1[i-1];
        } else if (dp[i][j].second == Direction::UP) {
            print_lcs(text1, dp, i-1, j);
        } else {
            print_lcs(text1, dp, i, j-1);
        }
    }
};

int main() {
    Solution sol;
    // string text1 = "abcde";
    // string text2 = "ace";

    // string text1 = "abc";
    // string text2 = "def";

    string text1 = "ACCGGTCGAGTGCGCGGAAGCCGGCCGAA";
    string text2 = "GTCGTTCGGAATGCCGTTGCTCTGTAAA";

    auto res = sol.longestCommonSubsequence(text1, text2);
    cout << "LCS length: " << res[text1.size()][text2.size()].first << " ";
    sol.print_lcs(text1, res, text1.size(), text2.size());
    cout << endl;
}
