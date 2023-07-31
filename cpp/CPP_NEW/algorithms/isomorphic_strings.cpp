/*
 * Given two strings s and t, determine if they are isomorphic.
 * Two strings s and t are isomorphic if the characters in s can be replaced to get t.
 * All occurrences of a character must be replaced with another character while preserving the order of characters.
 * No two characters may map to the same character, but a character may map to itself.
 */

#include <iostream>
#include <unordered_map>
#include <string>
using namespace std;

bool is_isomorphic(string_view s, string_view t) {
    if (s.size() != t.size()) return false;
    std::unordered_map<char, char> fs{};
    std::unordered_map<char, char> sf{};

    for(int i = 0; i < s.size(); ++i) {
        auto fs_iter = fs.find(s[i]);
        auto sf_iter = sf.find(t[i]);
        if(fs_iter != fs.end() && fs_iter->second != t[i]) return false;
        if(sf_iter != sf.end() && sf_iter->second != s[i]) return false;

        fs[s[i]] = t[i];
        sf[t[i]] = s[i];
    }
    return true;
}

int main() {
//    string s = "egg", t = "add";
//    string s = "foo", t = "bar";
    string s = "paper", t = "title";

    auto res = is_isomorphic(s, t);
    cout << s << " and " << t << (res ? " ARE ISOMORPHIC" : " ARE NOT ISOMORPHIC") << endl;
}