#include <iostream>
#include <string>
#include <future>
#include <thread>
#include <mutex>
#include <syncstream>
#include <latch>
#include <chrono>
#include <cxxabi.h>
#include <unordered_map>
#include <functional>
#include <memory>
#include <cassert>
#include <iomanip>
#include <cmath>
using namespace std;
using namespace std::chrono;
using namespace std::literals;

class Solution {
public:
    string fractionToDecimal(int numerator, int denominator) {
        assert(denominator != 0);
        if (numerator == 0) return "0";
        string res{};
        char ch{};
        // if exactly one of num or denom is negative, append "-" sign to res.
        if((numerator < 0 && denominator > 0) || (numerator > 0  && denominator < 0)) res.push_back('-');
        std::uint64_t dividend  = abs(static_cast<int64_t>(numerator));
        std::uint64_t divisor  = abs(static_cast<int64_t>(denominator));
        res.append(std::to_string(dividend / divisor));
        if(dividend % divisor == 0) return res;
        auto remainder = dividend % divisor;
        res.push_back('.');

        std::unordered_map<uint64_t, uint64_t> m{};
        while(remainder != 0) {
            if (m.find(remainder) != m.end()) {
                auto index = m[remainder];
                res.insert(index, "(");
                res.push_back(')');
                return res;
            } else {
                m[remainder] = res.size();
                remainder *= 10;
                ch = static_cast<char>((remainder / divisor) + '0');
                res.push_back(ch);
                remainder %= divisor;
            }
        }
        return res;
    }
};
int main() {
    Solution sol;
    cout << "1/2: " << sol.fractionToDecimal(1, 2) << endl;
    cout << "5/12: " << sol.fractionToDecimal(5, 12) << endl;
    cout << "4/333: " << sol.fractionToDecimal(4, 333) << endl;
    cout << "-50/8: " << sol.fractionToDecimal(-50, 8) << endl;
    cout << "-1/-2147483648: " << sol.fractionToDecimal(-1, -2147483648) << endl;
}