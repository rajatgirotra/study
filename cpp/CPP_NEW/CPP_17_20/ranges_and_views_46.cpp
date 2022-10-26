#include <iostream>
#include <vector>
#include <ranges>
#include <algorithm>
using namespace std;
namespace rng = std::ranges;

int main() {
    std::vector intVec {76, 12, 34, 6, -98, 45, -789};
    rng::sort(intVec);

    for(auto&& item : intVec) {
        cout << item << "  ";
    }
    cout << endl;
}