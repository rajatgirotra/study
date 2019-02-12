/*
 * Very trivial. Reverse iterator is an iterator adaptor which holds an underlying iterator.
 * The c'tor for reverse_iterator takes in iterator as you will see below. The important thing to note is that a reverse_iterator always
 * returns the next item in the container when it is de-referenced, instead of giving the item it is pointing to.
 *
 * For normal iterator:
 *
 * begin() --> points to the first element.
 * end() --> points to the end element + 1.
 *
 * for Reverse iterator
 * rbegin() --> end() for normal iterator. So that de-referencing it will return the last element
 * rend() --> begin() for normal iterator.
 *
 * If container items are
 * 1  2  3  4  5  6  7  8  9
 *          ^
 *          |
 *          |
 * and reverse_iterator is pointing to 4. then de-referencing will return 3.
 * and *(revIter.base()) will return 4.
 */

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
using namespace std;

namespace {
    // function to trim spaces from left and right of a string in place
    void ltrim(string& s) {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](char ch) {
            return !std::isspace(ch);
        }));
    }

    void rtrim(string& s) {
        s.erase(std::find_if(s.rbegin(), s.rend(), [](char ch) {
            return !std::isspace(ch);
        }).base(), s.end());
    }

    void trim(string &s) {
        ltrim(s);
        rtrim(s);
    }
}

int main() {
    vector<string> v{"Hello", "World", "Goodbye", "Cruel", "World"};
    // get a reverse iterator and iterate over it.

    vector<string>::reverse_iterator it(v.end());
    while(it != v.rend()) {
        cout << *it << endl;
        ++it;
    }

    // generally instead of creating reverse_iterator the way you created above, consider the more explicit approach below
    cout << endl;
    vector<string>::reverse_iterator iter = v.rbegin();
    while(iter != v.rend()) {
        cout << *iter << endl;
        ++iter;
    }

    // or use the convenience function make_reverse_iterator()
    cout << endl;
    std::copy(make_reverse_iterator(v.end()), make_reverse_iterator(v.begin()), ostream_iterator<string>(cout, "\n"));

    string s = "               Hello             ";
    trim(s);
    cout << "trimmed string: " << s << " another string\n";
}