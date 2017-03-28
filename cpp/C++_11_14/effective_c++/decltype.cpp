#include <iostream>
#include <vector>
using namespace std;

// template <typename Container, typename Index>
// auto getValueAtIndex(Container& c, Index i) {
//     return c[i];
// }

template <typename Container, typename Index>
decltype(auto) getValueAtIndex(Container&& c, Index i) {
    return std::forward<Container>(c)[i];
}

vector<double> doubleVector() {
    return vector<double> {1.1, 2.2, 3.3, 4.4, 5.5 };
}

int main() {
    auto dblVec = doubleVector();

    getValueAtIndex(dblVec, 0) = 10.1;
    cout << getValueAtIndex(dblVec, 0) << endl;

    getValueAtIndex(doubleVector(), 1) = 20.2;
    return 0;
}
