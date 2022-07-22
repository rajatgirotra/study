#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>
using namespace std;

int solution(const vector<int>& A, int R) {
    // items and their shelves count
    std::unordered_map<int, int> itemCountCopy;
    for(auto&& val : A) {
        itemCountCopy[val] += 1;
    }

    size_t max_items = 0;

    for(auto idx = R-1; idx < A.size(); ++idx) {
        size_t items_out = 0;
	auto itemCount {itemCountCopy};
        for(auto j = 0; j < R; ++j) {
            auto item_idx = idx - j;
            --itemCount[item_idx];
            if (itemCount[item_idx] == 0) {
                ++items_out;
            }
        }
	//cout << "items_out: " << items_out << endl;
        max_items = std::max(itemCountCopy.size() - items_out, max_items);
	//cout << "max_items: " << max_items << endl;
    }
    return max_items;
}

int main() {
    //std::vector<int> arr{2, 1, 2, 3, 2, 2};
    //cout << solution(arr, 3) << endl;
    
    std::vector<int> arr{2, 3, 1, 1, 2};
    cout << solution(arr, 2) << endl;
    return 0;
}

