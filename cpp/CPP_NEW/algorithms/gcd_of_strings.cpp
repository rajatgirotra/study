/*
 * For two strings s and t, we say "t divides s" if and only if s = t + ... + t (i.e., t is concatenated with itself one or more times).
 * Given two strings str1 and str2, return the largest string x such that x divides both str1 and str2.
 */

#include <iostream>
#include <string>
#include <string_view>
#include <algorithm>
using namespace std;

bool is_divisor(string_view s1, string_view s2, string_view shorter_str, int i) {
    int sz = i+1;
    if(s1.size() % sz != 0 || s2.size() % sz != 0) return false;

    auto f1 = s1.size() / sz;
    auto f2 = s2.size() / sz;
    auto possible_gcd = shorter_str.substr(0, i+1);
    string s1_temp{}, s2_temp{};
    for(int j = 0; j < f1; ++j) {
        s1_temp.append(possible_gcd);
    }
    for(int j = 0; j < f2; ++j) {
        s2_temp.append(possible_gcd);
    }
    if(s1_temp == s1 && s2_temp == s2) return true;
    else return false;
}

string gcd_strings(string_view s1, string_view s2) {
    // if either string is empty, return empty string
    string res{};
    if(s1.empty() || s2.empty()) return res;

    // max gcd of strings of length m and n will be min(m, n). so start with the minimum string length down to 0.
    auto shorter_str = (s1.size() < s2.size() ? s1 : s2);
    for(int i = shorter_str.size() - 1; i >= 0; --i) {
        if (is_divisor(s1, s2, shorter_str, i)) return string(shorter_str.substr(0, i+1));
    }
    return res;
}

int main() {
//    string str1 = "ABCABC";
//    string str2 = "ABC";

//    string str1 = "ABABAB";
//    string str2 = "ABAB";

    string str1 = "LEET";
    string str2 = "CODE";


    auto res = gcd_strings(str1, str2);
    cout << "gcd of strings " << str1 << " and " << str2 << " is " << (res.empty() ? "<EMPTY>" : res) << endl;
}




