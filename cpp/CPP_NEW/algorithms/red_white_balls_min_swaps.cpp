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
    // get indices of all red balls
    std::vector<int> reds{};
    for(auto i = 0; i < s.size(); ++i) {
        if(s[i] == 'R') reds.push_back(i);
    }

    auto sp = 0;
    auto ep = reds.size()-1;
    int count{};
    while(sp < ep) {
        // reds[ep] - reds[sp] tells you how many total balls are there when you start from reds[sp] to reach reds[ep]
        // ep - sp - gives you how many of those balls above are actually red. So you don't need to swap red balls. So we subtract (ep-sp)
        count += reds[ep] - reds[sp] - ep + sp;
        ++sp;
        --ep;
    }
    return count;
}

int main() {
    string s{"RWWWRWRWWR"};
    cout << solution(s) << endl;
}
