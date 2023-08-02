/*
 * given integer n, print all possible parenthesizations using n pairs of opening and closing parenthesis
 */

#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>
#include <cassert>
using namespace std;

/*
 * openN = number of opening braces left to put in the string
 * closeN = number of closing braces left to put in the string
 * if openN == closeN, we can only put an opening brace.
 * if closeN > openN, we can put either an opening brace or a closing brace
 */
void get_parenthesis_helper(int n, int openN, int closeN,  std::string& permutation, std::vector<string>& res) {
    if(openN == 0 && closeN == 0) {
        assert(permutation.size() == 2*n);
        res.emplace_back(permutation);
    }

    if(openN != 0) {
        permutation.push_back('(');
        get_parenthesis_helper(n, openN-1, closeN, permutation, res);
        permutation.pop_back();
    }
    if(closeN != 0 && closeN > openN) {
        permutation.push_back(')');
        get_parenthesis_helper(n, openN, closeN-1, permutation, res);
        permutation.pop_back();
    }
}

std::vector<string> get_parenthesis(int n) {
    std::string permutation;
    std::vector<string> res;
    get_parenthesis_helper(n, n, n, permutation, res);
    return res;
}

int main() {
    auto res = get_parenthesis(4);
    cout << "[ ";
    std::copy(begin(res), end(res)-1, ostream_iterator<string>(cout, ", "));
    cout << *res.rbegin() << " ]\n";
}

