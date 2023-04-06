/*
given an array of integers. find the length of the largest spike you can create. A spike is formed by creating a strictly increasing sequence followed by a scratchily decreasing sequence. Each element can only be used once. You need not select all elements in the array.
 Example: arr = [1, 2], answer = 2 as [1, 2] is already an increasing spike. A decreasing spike isnt necessary.
 Example: arr = [2, 5, 3, 2, 4, 1], answer = 6 [2, 4, 5, 3, 2, 1] or [1, 2, 3, 4, 5, 2] (2 occurs twice and so is used at max twice only).
 Example: arr = [2, 3, 3, 2, 2, 2, 1], answer = 4 [2, 3, 2, 1] or [1, 2, 3, 2]
Can do easily by creating two sets. One in increasing order and one in decreasing order.
*/
#include <iostream>
#include <set>
#include <string>
#include <array>
using namespace std;

int main() {
    //std::array<int, 2> arr {1, 2};
    //std::array<int, 6> arr {2, 5, 3, 2, 4, 1};
    std::array<int, 7> arr {2, 3, 3, 2, 2, 2, 1};

    std::set<int, std::less<>> increasing_seq;
    std::set<int, std::greater<>> decreasing_seq;

    for(auto&& item : arr) {
        if(increasing_seq.find(item) == increasing_seq.end()) {
            increasing_seq.emplace(item);
        } else {
            decreasing_seq.emplace(item);
        }
    }

    // count length of longest spike
    auto sz = increasing_seq.size() + decreasing_seq.size();
    if (!decreasing_seq.empty() && (*increasing_seq.rbegin() == *decreasing_seq.begin())) {
        --sz;
    }

    cout << "Length of longest spike: " << sz << endl;

}