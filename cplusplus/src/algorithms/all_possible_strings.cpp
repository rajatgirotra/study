/*
* Print all possible strings of length k that can be formed from a set of n characters
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
#include <set>
#include <vector>
#include <cstdint>
using namespace std;

void permHelper(const std::set<char>& charSet, int K, std::string &permutation,
                          std::vector<bool> &used, vector<string>& res) {
    // have we reached our goal?
    if (permutation.size() == K) {
        res.emplace_back(permutation);
        return;
    }

    // make a choice
    for (int i = 0; i < K; ++i) {
        if (used[i] || i > permutation.size()) {
            continue;
        }
        for (auto ch : charSet) {
            used[i] = true;
            permutation.push_back(ch);
            permHelper(charSet, K, permutation, used, res);
            used[i] = false;
            permutation.pop_back();
        }
    }
}

vector<string> permutations(const std::set<char> &charSet, int K) {
    std::string permutation;
    std::vector<string> res;
    std::vector<bool> used(K, false);
    permHelper(charSet, K, permutation, used, res);
    return res;
}

int main() {
    //    std::set<char> charSet {'a', 'b', 'c', 'd'};
    //    int K = 2;

    std::set<char> charSet{'a', 'b'};
    int K = 3;

    auto res = permutations(charSet, K);
    cout << "permutations:\n";
    for (auto &&item: res) {
        cout << item << endl;
    }
    return 0;
}
