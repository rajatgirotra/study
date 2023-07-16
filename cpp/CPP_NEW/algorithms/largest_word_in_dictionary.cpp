/*
 * Given a dictionary of the words(strings) which contains different words & you are given an input string e.g. “abd”. You need to find the largest word
 * available in the supplied dictionary which can be made using the letters of input string. The returned word can contain only the same
 * no of occurrences of the letters as given in the input string i.e. if a letter is given once then in the output it should be existed only once.
 * Examples:
 * 1, Dictionary {“to”, “banana”, “toe”, “dogs”, “ababcd”, “elephant”} and input string is “eot”. Output should be “toe”
 * 2, Dictionary is same as specified in example a but the input string is “ogtdes” and the output is “dogs” and “toes”
 */
#include <iostream>
#include <string>
#include <set>
#include <algorithm>
using namespace std;

auto largest_word_in_dictionary(const std::set<std::string>& dictionary, const std::string& input) {
    std::array<int, 256> ch{};
    for(auto&& c : input) {
        ++(ch[static_cast<int>(c)]);
    }

    std::set<string> res{};
    int maxLen {0};
    for(auto&& word : dictionary) {
        std::array<int, 256> in(ch);
        bool possible{true};
        for(auto&& c : word) {
            if (in[static_cast<int>(c)] <= 0) {
                possible = false;
                break; // move to next word, as this word cannot be in output
            } else {
                --(in[static_cast<int>(c)]);
            }
        }
        if(possible) {
            if(maxLen == word.size()) {
                res.emplace(word);
            } else if (maxLen < word.size()) {
                maxLen = word.size();
                res.clear();
                res.emplace(word);
            }
        }
    }
    return res;
}

int main() {
    std::set<std::string> dictionary {"to", "banana", "toes", "dogs", "ababcd", "elephant"};
    std::string input{"ogtdes"};

    auto res = largest_word_in_dictionary(dictionary, input);
    for(auto&& r : res) {
        cout << r << endl;
    }
}