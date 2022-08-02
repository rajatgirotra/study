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
#include <algorithm>
#include <vector>
#include <array>
#include <utility>
#include <cmath>
#include <set>
using namespace std;

void permHelper(vector<string>& res, const std::set<char>& charSet, int K, string& permutation, vector<bool>& used) {
    if(permutation.size() == K) {
        res.emplace_back(permutation);
        return;
    }
    for(int i = 0; i < K; ++i) {
        if ((used[i]) || (permutation.size() < i))
           continue; // go to next iteration of i
        for(auto&& j : charSet) {
            if ((permutation.empty()) || (std::abs(permutation[i-1] - j) >= 0)) {
                // make a choice
                used[i] = true;
                permutation.push_back(j);
                // backtrack
                permHelper(res, charSet, K, permutation, used);
                // undo choice
                used[i] = false;
                permutation.pop_back();
            }
        }
    }
}

vector<string> permutations(const std::set<char>& charSet, int K) {
    vector<string> res {};
    string permutation{};
    vector<bool> used(K, false);
    permHelper(res, charSet, K, permutation, used);
    return res;
}

int main() {
   std::set<char> charSet {'a', 'b', 'c', 'd'};
   int K = 1;

   //std::set<char> charSet {'a', 'b'};
   //int K = 3;
   auto res = permutations(charSet, K);
   cout << "permutations:\n";
   for(auto&& item : res) {
      cout << item << endl;
   }
   return 0;
}
