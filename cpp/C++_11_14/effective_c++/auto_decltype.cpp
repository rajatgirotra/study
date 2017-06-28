#include <iostream>
#include <vector>
using namespace std;

template <typename Container, typename Index>
auto getValueAtIndex(Container&& c, Index i) -> decltype(std::forward<Container>(c)[i]) {
    return c[i];
}

vector<double> doubleVector() {
    return vector<double> {1.1, 2.2, 3.3, 4.4, 5.5 };
}

int main() {
    auto dblVec = doubleVector();
    cout << getValueAtIndex(dblVec, 0) << endl;
    cout << getValueAtIndex(doubleVector(), 1) << endl;

    getValueAtIndex(dblVec, 0) = 6.6;
    cout << getValueAtIndex(dblVec, 0) << endl;
    return 0;
}
