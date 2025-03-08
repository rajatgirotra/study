/*
* Consider all words of length N, containing only letters 'a', 'b', 'c' with no two identical neighboring letters. Example 'aba' is such a word, but not 'abb'
 * Find K alphabetically smallest words of length N that do not contain identical neighboring letters.
 * This is a backtracking problem. You can find out if an algorithm requires backtracking by looking at two things.
 * 1) Does it involve creating a decision tree?? (we call it a state space tree)
 * 2) Do we need to find all possible solutions?? If yes, it is likely a backtracking problem.
 * The general structure of a backtracking is based on 3 things
 * choices --> At each stage you need to make a choice
 * constraint --> At each stage you have a constraint.
 * goals --> the goals you need to reach
 *
 * Algo
 * ----
 *  BACKTRACK(res, nums) --> res is the goal, and nums is the input
 *  if (GOAL REACHED)
 *  {
 *      ADD GOAL TO res
 *      return
 *  }
 *  for(int i = 0; i < NB_CHOICES; ++i) // NB_CHOICES = nums.size() mostly
 *  {
 *      if(CHOICE[i] is valid)
 *      {
 *          Make CHOICE[i]
 *
 *          BACKTRACK(res, nums) // recursive call
 *
 *          Undo CHOICE[i]
 *      }
 *  }
 *
 */
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <array>
#include <utility>
#include <cmath>
using namespace std;

void permHelper(vector<string> &res, int N, int K, std::string &permutation, vector<bool> &used) {
    if (permutation.size() == N) {
        res.emplace_back(permutation);
        return;
    }
    static std::array<char, 3> choices{'a', 'b', 'c'};
    for (int i = 0; i < N; ++i) {
        if (used[i] || i > permutation.size()) continue;
        for (auto ch: choices) {
            if (i > 0 && permutation[i - 1] == ch) continue;
            used[i] = true;
            permutation.push_back(ch);
            permHelper(res, N, K, permutation, used);
            used[i] = false;
            permutation.pop_back();
            if (res.size() == K) {
                return;
            }
        }
    }
}

vector<string> permutations(int N, int K) {
    vector<string> res{};
    string permutation{};
    vector<bool> used(N, false);
    permHelper(res, N, K, permutation, used);
    return res;
}

int main() {
    int N = 5;
    int K = 6;
    auto res = permutations(N, K);
    cout << "permutations:\n";
    for (auto &&item: res) {
        cout << item << endl;
    }
    return 0;
}
