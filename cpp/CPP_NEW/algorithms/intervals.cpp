/*Question:
A popular online retailer allows vendors to specify different prices in advance
for the same item throughout the day. We now need to design an algorithm that
helps identify the lowest price for the item at any point of the day.

Assumptions:

For the algorithm, assume all vendors are selling the same product
and there is only one product being sold. Given a list that has
        vendor information - ( startTime, endTime, price ) of the deal,
return a sorted list with different possible intervals and
        the least price of the product during the interval.

The interval is inclusive of start and end time.

All the 3 values passed by the vendor are integers.

sampleInput = { new Interval( 1, 5, 20 ), new Interval( 3, 8, 15 ), new Interval( 7, 10, 8 ) };
expectedOutput = { new Interval( 1, 2, 20 ), new Interval( 3, 6, 15 ), new Interval( 7, 10, 8 ) };
 */

#include <iostream>
#include <unordered_map>
#include <map>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <utility>
using namespace std;

class Interval {
public:
    int m_start;
    int m_end;
    int m_price;

    Interval(int s, int e, int p) : m_start(s), m_end(e), m_price(p) {}

    friend ostream& operator << (ostream& os, const Interval& rhs) {
        os << "(" << rhs.m_start << ", " << rhs.m_end << ", " << rhs.m_price << ")";
        return os;
    }

    bool operator < (const Interval& rhs) const noexcept {
        return m_start < rhs.m_start;
    }
};

int main() {
    std::vector<Interval> input{{1, 5, 20}, {3, 8, 15}, {7, 10, 8}};
    cout << "Input:\n";
    for(auto&& interval : input) {
        cout << interval << endl;
    }

    std::map<int, int> startPriceMap{};
    for(auto&& [s, e, p] : input) {
        for(int i = s; i <= e; ++i) {
            auto iter = startPriceMap.find(i);
            if(iter != startPriceMap.end()) {
                iter->second = std::min(p, iter->second);
            } else {
                startPriceMap[i] = p;
            }
        }
    }

    cout << "startPriceMap\n";
    for(auto&& [k, v] : startPriceMap) {
        cout << k << "  --> " << v << endl;
    }

    std::vector<Interval> res;
    for(auto&& [key, value] : startPriceMap) {
        if (res.empty()) {
            res.emplace_back(key, key, value);
        } else {
            if (res[res.size()-1].m_price == value) {
                res[res.size()-1].m_end = key;
            } else {
                res.emplace_back(key, key, value);
            }
        }
    }

    cout << "final intervals\n";
    for(auto&& interval : res) {
        cout << interval << endl;
    }
}