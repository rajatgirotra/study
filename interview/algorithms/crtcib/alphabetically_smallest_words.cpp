/*
 * Consider all words of length N, containing only letters 'a', 'b', 'c' with no two identical neighoring letters. Example 'aba' is such a word, but not 'abb'
 * Find K alphabetically smallest words of length N that do not contain identical neighoring letters.
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

void permHelper(vector<string>& res, int N, int K, string& permutation, vector<bool>& used) {
    static const string s{"abc"};
    if(permutation.size() == N) {
        res.emplace_back(permutation);
        return;
    }
    for(int i = 0; i < N; ++i) {
        if ((used[i]) || (permutation.size() < i))
           continue; // go to next iteration of i
        for(int j = 'a'; j <= 'c'; ++j) {
            if ((permutation.empty()) || (std::abs(permutation[i-1] - j) >= 1)) {
                // make a choice
                used[i] = true;
                permutation.push_back(j);
                // backtrack
                permHelper(res, N, K, permutation, used);
                // undo choice
                used[i] = false;
                permutation.pop_back();

                // return if we have processed K permutations
                if(res.size() == K) return;
            }
        }
    }
}

vector<string> permutations(int N, int K) {
    vector<string> res {};
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
   for(auto&& item : res) {
      cout << item << endl;
   }
   return 0;
}
