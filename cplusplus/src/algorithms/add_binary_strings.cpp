/* Given two binary strings a and b, return their sum as a binary string.
Example 1:

Input: a = "11", b = "1"
Output: "100"
Example 2:

Input: a = "1010", b = "1011"
Output: "10101"
 */

#include <algorithm>
#include <iostream>
#include <string>
using namespace std;


class Solution {
public:
    string addBinary(string a, string b) {
        int i = a.size()-1, j = b.size()-1;
        int carry = 0;

        string res{};
        while (i >= 0 || j >= 0 || carry) {
            auto sum = carry;
            if (i >= 0)  sum += a[i--] - '0';
            if (j >= 0)  sum += b[j--] - '0';

            res += (sum % 2) + '0';
            carry = (sum /= 2);
        }
        ranges::reverse(res);
        return res;
    }
};

int main() {
    // string s1{"11"}, s2{"1"};
    string s1{"1010"}, s2{"1011"};

    cout << Solution().addBinary(s1, s2) << endl;
}

