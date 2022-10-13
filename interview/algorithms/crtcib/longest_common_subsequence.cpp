/*
Longest common subsequence.

*/
#include <iostream>
#include <algorithm>
#include <random>
#include <iterator>
#include <limits>
#include <iomanip>
#include <cstring>
#include <utility>
#include <ctime>
#include <array>
#include <deque>
#include <cassert>
#include <unordered_map>
#include <ostream>
#include <string>
using namespace std;

template <size_t X, size_t Y>
void print_lcs(char direction[X][Y], const std::array<char, X>& text1, size_t t1_sz, size_t t2_sz) {
    if(t1_sz == 0 || t2_sz == 0) {
        return;
    }
    if(direction[t1_sz][t2_sz] == 'D') {
        print_lcs(direction, text1, t1_sz-1, t2_sz-1);
        cout << " " << text1[t1_sz-1];
    } else if(direction[t1_sz][t2_sz] == 'L') {
        print_lcs(direction, text1, t1_sz, t2_sz-1);
    } else {
        print_lcs(direction, text1, t1_sz-1, t2_sz);
    }
}

template <size_t X, size_t Y>
int LCS(const std::array<char, X>& text1, const std::array<char, Y>& text2) {
    int lcs[X+1][Y+1] {};
    char direction[X+1][Y+1] {};

    for(size_t i = 0; i < X; ++i) {
        for(size_t j = 0; j < Y; ++j) {
            if(text1[i] == text2[j]) {
                lcs[i+1][j+1] = lcs[i][j] + 1;
                direction[i+1][j+1] = 'D';
            } else {
                if(lcs[i][j+1] > lcs[i+1][j]) {
                    lcs[i+1][j+1] = lcs[i][j+1];
                    direction[i+1][j+1] = 'U';
                } else {
                    lcs[i+1][j+1] = lcs[i+1][j];
                    direction[i+1][j+1] = 'L';
                }
            }
        }
    }
    // print LCS
    cout << "Longest Common Subsequence: ";
    print_lcs(direction, text1, X, Y);
    cout << endl;
    return lcs[X][Y];
}

int main() {
    // std::array<char, 7> text1 {'G', 'X', 'T', 'X', 'A', 'Y', 'B'};
    // std::array<char, 6> text2 {'A', 'G', 'G', 'T', 'A', 'B'};

    std::array<char, 7> text1 {'A', 'B', 'C', 'B', 'D', 'A', 'B'};
    std::array<char, 6> text2 {'B', 'D', 'C', 'A', 'B', 'A'};

    std::copy(begin(text1), end(text1), std::ostream_iterator<char>(cout, ""));
    cout << endl;
    std::copy(begin(text2), end(text2), std::ostream_iterator<char>(cout, ""));
    cout << endl;

    auto len = LCS(text1, text2);
    cout << "LCS Length: " << len << endl;
}
