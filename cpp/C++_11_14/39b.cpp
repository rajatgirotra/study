// std::reference_wrapper

#include <iostream>
#include <functional>
#include <utility>
#include <list>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int main() {
    std::list<int> l(10);
    std::iota(l.begin(), l.end(), -4);  // std::iota initializes the list with -4, -3,  -2 and so on.

    std::vector<std::reference_wrapper<int>> v(l.begin(), l.end()); // vector is just holding pointers to objects in the list.
    
    std::random_shuffle(v.begin(), v.end()); // just random shuffle items in the vector.
    
    cout << "\nContents of list: " << endl;
    for(auto i : l) {
        cout << i << " " ;
    }
   
    cout << "\nContents of vector: " << endl;
    for(auto i : v) {
        cout << i << " " ;
    }

    // double elements in the vector
    for(auto& i : v) {
        i *= 2;
    }
 
    cout << "\nContents of list after double: " << endl;
    for(auto i : l) {
        cout << i << " " ;
    }

    int i, j;
    auto r = std::ref(i); // r refers to i, its like r refers to i and is also copyable and assignable
    r = std::ref(j); // Okay; r refers to j now.
    j = 100;
    cout << "\n" << r << endl;
   
    return 0;
}
   
