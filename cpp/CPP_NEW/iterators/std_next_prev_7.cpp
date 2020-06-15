/*
 * C++11 introduced std::next() and std::prev() to advance forward or backward the Iterator by Distance n.
 * Actually std::advance() already does it, but it returns void. std::next(), prev() use std::advance() and also return the
 * advanced iterator
 *
 * template <typename Iterator, Distance n>
 * Iterator next(Iterator it, Distance n) {
 *     std::advance(it, n);
 *     return it;
 * }
 */
#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <string>
using namespace  std;

int main() {
    vector<string> v {"Rajat", "Vidhu", "Myra", "Viraj"};
    auto it = v.begin();
    it = std::next(it, 3); // it should now be at "Viraj"
    cout << *it << endl;
    it = std::prev(it, 2); // it should now be at "Vidhu"
    cout << *it << endl;
}