/*
 * approximate string matching (often referred to as fuzzy string searching) is the technique of finding strings that match a pattern approximately (rather than exactly).
 *
 * The closeness of a match is measured in terms of the number of primitive operations necessary to convert the string into an exact match. This number is called the edit distance between the string and the pattern. The usual primitive operations are
 * insertion
 * deletion
 * substitution
 *
 * Write a progra given a pattern p, a string s, and the number of edit allowed k only edits are allowed, not insertions and deletions. Find if pattern p matches the string s with at most k edits. Example:
 *
 * s  = A B B A D E B A A A A A D
 * p  = B C A
 * k = 1
 *
 * output should be True as B B A at index 1 and B A A at index 6 can be converted to B C A with max 1 edit
 */

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <unordered_set>
#include <cmath>
using namespace std;

bool solution(const string& s, const string& p, int k) {
    int segments = k + 1;
    // break pattern into k+1 segments
    int segment_length = std::ceil(static_cast<double>(p.size()) / segments);

    std::unordered_set<int> all_matches {}; // set of indices in text 's' which matches pattern 'p' with k or fewer edits.

    // for each segment try to find the index of substring in text 's'. if indeed p matches s with k or fewer edits.
    // then atleast one segment will match a substring in text 's' exactly.
    for(int i = 0; i < segments; ++i) {

        // left and right indices for every segment
        int l = segment_length * i;
        int r = std::min(l + segment_length - 1, static_cast<int>(p.size() - 1));

        // find substring
        size_t t_idx = 0, pos = 0;
        std::vector<size_t> matches{};
        do {
            pos = s.find(std::addressof(p[l]), t_idx, r-l+1);
            if(pos != string::npos) {
                matches.emplace_back(pos);
                t_idx = pos+1;
            }
        } while(pos != string::npos);

        // for every match. try to match the prefix of the segment and the postfix of the segment to text s and count the mismatches.
        for(auto&& m : matches) {
            if (m < l || (m - l + p.size() > s.size())) {
               continue;
            }
            auto mismatches {0};
            for (int j = 0; j < l; ++j) {
                if (p[j] != s[m - l + j]) {
                   ++mismatches;
                }
            } 
            for (int j = r+1; j < p.size()-1; ++j) {
                if(p[j] != s[m -l + j]) {
                   ++mismatches;
                   if (mismatches > k)
                       break;
                }
            }
            if (mismatches <= k) {
                all_matches.emplace(m-l);
            }
        }
    }
    if (!all_matches.empty()) {
        for(auto&& m : all_matches) {
            cout << "approximate match at index: "<< m << endl;
        }
    }
    return !all_matches.empty();
}

int main() {
    string text {"ABBADEBAAAAAD"};
    string pattern {"BCA"};
    cout << solution(text, pattern, 1) << endl; // should be True
}
