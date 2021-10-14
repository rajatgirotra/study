/*
 * C++ has an std::search() algorithm which searches for a pattern in a text.
 * m --> is the size of the pattern
 * n --> is the size of the string
 * k --> is the size of the input alphabet (i.e. list of all possible values of characters in the string. eg k = 26 for all lower case alphabets)
 *
 * before c++17, std::search() just performed the naive string matching algorithm which has time complexity of O(mn).
 * But with C++17, there are two other ways.
 * 1) use a execution policy to speed up: like std::execution::par,
 * 2) Provide a searcher object. Like KMP searcher, Boyer Moore Searcher etc.
 *
 * Searcher and Execution Policy cannot be mixed.
 * string search algorithms like KMP, Boyer Moore perform some kind of pre-processing stage that is later used to skip fruitless comparisons.
 * This pre-processing takes time proportional to m and k.
 */

#include <algorithm>
#include <iostream>
#include <string>
#include <functional>
using namespace std;

namespace {
    struct ichar_hash {
        size_t operator()(const char& ch) const noexcept {
            auto key = std::hash<int>{}(std::tolower(ch));
            return key;
        }
    };
}

int main() {
    const string text{"SuperHelloWorld"};
    const string pattern{"Hello"};

    auto it = std::search(begin(text), end(text), std::boyer_moore_horspool_searcher(begin(pattern), end(pattern)));
    if (it != text.end()) {
        cout << "Pattern [" << pattern << "] found at index: " << std::distance(text.begin(), it) << endl;
    } else {
        cout << "Pattern [" << pattern << "] not found." << endl;
    }

    // same as above but using Boyer Moore Algo
    const string text2 {"SUPER HELLO WORLD"};
    const string pattern2 {"HELLO"};

    it = std::search(begin(text2), end(text2), std::boyer_moore_horspool_searcher(begin(pattern2), end(pattern2)));
    if (it != text2.end()) {
        cout << "Pattern [" << pattern2 << "] found at index: " << std::distance(text2.begin(), it) << endl;
    } else {
        cout << "Pattern [" << pattern2 << "] not found." << endl;
    }

    // Boyer Moore but case insensitive
    const string text3 {"SUPER HELLO WORLD"};
    const string pattern3 {"hello"};

    it = std::search(
            begin(text3), end(text3),
            std::boyer_moore_horspool_searcher(
                    begin(pattern3), end(pattern3),
                    [](const char& ch) {
                        return std::hash<int>{}(std::tolower(ch));
                    },
                    [](const char& lhs, const char& rhs) {
                      return tolower(lhs) == tolower(rhs);
                    }));
    if (it != text3.end()) {
        cout << "Pattern [" << pattern3 << "] found at index: " << std::distance(text3.begin(), it) << endl;
    } else {
        cout << "Pattern [" << pattern3 << "] not found." << endl;
    }
}
