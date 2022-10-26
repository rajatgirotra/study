#include <iostream>
#include <vector>
#include <map>
#include <ranges>
#include <algorithm>
#include <iterator>
#include <string>
using namespace std;
namespace vws = std::views;
int main() {

    // map of composers (mapping their name to their year of birth):
    std::map<std::string, int> composers{
            {"Bach",        1685},
            {"Mozart",      1756},
            {"Beethoven",   1770},
            {"Tchaikovsky", 1840},
            {"Chopin",      1810},
            {"Vivaldi ",    1678},
    };

    // iterate over the names of the first three composers born since 1700.
    auto v = composers
             | vws::filter([](const auto &elem) { return elem.second >= 1700; })
             | vws::take(3)
             | vws::keys; // get only keys

    std::ranges::copy(v, std::ostream_iterator<string>(cout, "  "));
    cout << endl;

    // 2. another view that can generate its own values
    int arr[] {1, 2, 3, 4, 5};
    for(auto&& idx : vws::iota(0UL, sizeof(arr)/sizeof(arr[0]))) {
        cout << arr[idx] << " ";
    }
    cout << endl;
}