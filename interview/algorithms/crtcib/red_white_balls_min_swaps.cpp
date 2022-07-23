/*
 * There are N balls positioned in a row. Each of them is either red or white. In one move we can swap two adjacent balls. We want to arrange all the red balls into a consistent segment (i.e. bring all red balls together). What is the minimum number of swaps needed?
 * If count (no. of swaps is more than 10^9, ie 1 billion, return -1 instead)
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

// the strategy is to bring all Red Balls into the middle instead of bringing them together on the left or the right.

int solution(const string& s) {
    // first find out the index of all red balls
    std::vector<int> reds;
    for(auto idx = 0; idx < s.size(); ++idx) {
        if (s[idx] == 'R')
            reds.emplace_back(idx);
    }

    int count {0};
    size_t sp = 0, ep = reds.size()-1;
    while(sp < ep) {
        count += reds[ep] - reds[sp] -ep + sp;
        if(count > 1000000000) {
           return -1;
        }
        ++sp;
        --ep;
    }
    return count;
}

int main() {
    string s{"RWWWRWRWWR"};
    cout << solution(s) << endl;
}
