/*
 * Good example to show you the real use of auto keyword.
 */
#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> v;
    for (int i = 0; i < 10; ++i) {
        v.push_back(i);
    }

    // for(vector<int>::iterator iter = v.begin(); iter != v.end(); ++iter) { //See how much typing is saved.
    for (auto iter = v.begin(); iter != v.end(); ++iter) {
        cout << *iter << "\t";
    }
    cout << endl;

    return 0;
}
