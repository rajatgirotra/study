/*
 * Print all permutations of a string.
 * This is a backtracking problem. You can find out if an algorithm requires backtracking by looking at two things.
 * 1) Does it involve creating a decision tree?? (we call it a state tree)
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
using namespace std;

void permHelper(vector<string>& res, const string& s, string& permutation, vector<bool>& used) {
    if(permutation.size() == s.size()) {
        res.emplace_back(permutation);
        return;
    }
    for(int i = 0; i < s.size(); ++i) {
        if (!used[i]) {
            used[i] = true;
            permutation.push_back(s[i]);

            // backtrack
            permHelper(res, s, permutation, used);

            // undo choice
            used[i] = false;
            permutation.pop_back();
        }
    }
}

vector<string> permutations(const string& s) {
    vector<string> res {};
    vector<bool> used(s.size(), false);
    string permutation{};
    permHelper(res, s, permutation, used);
    return res;
}

int main() {
   string s("ABC");
   auto res = permutations(s);
   cout << "permutations of " << s << " are:\n";
   for(auto&& item : res) {
      cout << item << endl;
   }
   return 0;
}
