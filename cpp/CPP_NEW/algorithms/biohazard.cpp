#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <numeric>
using namespace std;

bool canCoExist(const std::vector<int>& arr, const std::unordered_map<int, std::vector<int>> poisonMap) {
    for(auto item : arr) {
        auto iter = poisonMap.find(item);
        if(iter != poisonMap.end()) {
            auto&& lst = iter->second;
            for(auto allergic : lst) {
                if(std::find(begin(arr), end(arr), allergic) != arr.end()) {
                    return false;
                }
            }
        }
    }
    return true;
}

std::uint32_t biohazard(int n, const std::vector<int>& allergic, const std::vector<int>& poison) {
    std::unordered_map<int, vector<int>> poisonMap{};
    for(int i = 0; i < poison.size(); ++i) {
        auto& lst = poisonMap[poison[i]];
        lst.emplace_back(allergic[i]);
    }
    int count{n};
    std::vector<int> bacteria(n);
    std::iota(begin(bacteria), end(bacteria), 1);
    for (int sz = 2; sz <= n; ++sz) {
        for(int start = 0; start <= n-sz; ++start) {
            std::vector<int> subArray(std::next(begin(bacteria), start), std::next(begin(bacteria), sz+start));
            if (canCoExist(subArray, poisonMap)) {
                ++count;
            }
        }
    }
    return count;
}

int main() {
#if 0
    std::vector<int> allergic{1, 2};
    std::vector<int> poison{3, 4};
    auto res = biohazard(4, allergic, poison);
#endif

#if 0
    std::vector<int> allergic{1, 2};
    std::vector<int> poison{3, 5};
    auto res = biohazard(5, allergic, poison);
#endif

#if 1
    std::vector<int> allergic{2, 1, 3};
    std::vector<int> poison{3, 3, 1};
    auto res = biohazard(3, allergic, poison);
#endif
    cout << res << endl;
}