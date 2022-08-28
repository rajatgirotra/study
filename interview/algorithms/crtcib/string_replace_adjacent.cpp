/*
Given a string containing only the characters 'A' 'B' 'C' 'D', return the string when all adjacent "AB" / "BA" and "CD" / "DC" pairs have been removed.
Example: CBACD -> CCD -> C, CABABD -> CABD -> CD -> "", "ACBDACBD" -> "ACBDACBD"
*/

#include <string>
#include <iostream>
#include <cassert>
using namespace std;

bool replace_helper(string& in, const string& pattern) {
    auto pos = in.find(pattern);
    if(pos == string::npos) return false;
    in.erase(pos, pattern.size());
    return true;
}

string replace_adjacent(string in) {
    static string pat1 {"AB"}, pat2 {"BA"}, pat3 {"CD"}, pat4 {"DC"};
    while(true) {
        auto res1 = replace_helper(in, pat1);
        auto res2 = replace_helper(in, pat2);
        auto res3 = replace_helper(in, pat3);
        auto res4 = replace_helper(in, pat4);
        if(!res1 && !res2 && !res3 && !res4) {
            return in;
        }
    }
}

int main(int argc, char** argv) {
    assert(argc == 2);

    string in(argv[1]);

    cout << "Input: " << in << ", Output: " << replace_adjacent(in) << endl;
}
