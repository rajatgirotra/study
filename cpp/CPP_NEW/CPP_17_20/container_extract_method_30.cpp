/*
 * C++17 provides extract() method on associative containers. The method returns you an opaque handle to the item,
 * and disassociates that element from the container. You can them modify that element and MOVE IT into another container.
 */

#include <iostream>
#include <set>
#include <string>
#include <algorithm>
#include <map>
using namespace std;

int main() {
    std::set<string> namesSet {"Rajat", "Vidhu", "Myra", "Viraj", "Unknown"};
    std::set<string> outSet;
    auto handle = namesSet.extract("Unknown");

    outSet.insert(std::move(handle)); // MOVE IT.

    cout << "NameSet\n";
    for(auto&& name : namesSet) {
        cout << name << " ";
    }
    cout << endl;

    cout << "OutSet\n";
    for(auto&& name : outSet) {
        cout << name << " ";
    }
    cout << endl;

    // you can use this technique to change the key of an item in a mao
    using NameRankMap = std::map<string, int>;
    NameRankMap nrm { {"Rajat", 1}, {"Vidhu", 2}, {"Myra", 3}, {"Viraj", 4}};
    cout << "NameRankMap\n";
    for(auto&& [k, v] : nrm) {
        cout << k << " has rank " << v << endl;
    }
    cout << endl;

    auto node = nrm.extract("Rajat");
    node.key() = string("RajatGirotra");
    nrm.insert(std::move(node));
    cout << "NameRankMap with changed key\n";
    for(auto&& [k, v] : nrm) {
        cout << k << " has rank " << v << endl;
    }
    cout << endl;

}
