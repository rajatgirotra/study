/*
Given a string containing only the characters 'A' 'B' 'C' 'D', return the string when all adjacent "AB" / "BA" and "CD" / "DC" pairs have been removed.
Example: CBACD -> CCD -> C, CABABD -> CABD -> CD -> "", "ACBDACBD" -> "ACBDACBD"
*/
#include <string>
#include <iostream>
#include <cassert>
#include <array>
using namespace std;

bool remove_pattern(string& in, const string& pattern) {
    // remove false if you remove a pattern, else return true
    auto pos = in.find(pattern);
    if(pos == string::npos) {
        return true;
    } else {
        in.erase(pos, pattern.size());
        return false;
    }
}

string remove_adjacent(string in) {
    static std::array<string, 4> patterns {"AB", "BA", "CD", "DC" };
    bool res{true};
    while(true) {
        for(auto&& pat : patterns) {
            res = res && remove_pattern(in, pat);
        }
        if(res) break;
        else res = true;
    }
    return in;
}

int main(int argc, char** argv) {
    assert(argc == 2);

    string in(argv[1]);

    cout << "Input: " << in << ", Output: " << remove_adjacent(in) << endl;
}
