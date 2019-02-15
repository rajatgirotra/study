#include "hash_combine.hpp"
#include <string>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <bitset>
#include <utility>
#include <ostream>
using namespace std;

namespace {
    void printMap(const std::string& name, auto&& m) {
        cout << "----------------" << name << "-----------------------------\n";
        for(auto&& item : m) {
            cout << item.first << " --> " << item.second << endl;
        }
        cout << "----------------------------------------------\n";
    }

    struct Key {
        string firstname;
        string lastname;

        friend ostream& operator << (ostream& os, const Key& rhs) {
            os << rhs.lastname << ", " << rhs.firstname;
            return os;
        }

    };

    struct KeyEqual {
        bool operator ()(const Key& lhs, const Key& rhs) const noexcept {
            return (lhs.firstname == rhs.firstname) && (lhs.lastname == rhs.lastname);
        }
    };

    struct KeyHash {
        std::size_t operator() (const Key& key) const noexcept {
            ::hash_combiner::hash<string, string> hasher{};
            return hasher(key.firstname, key.lastname);
        }
    };

    // using lambda's as Hash and Predicate
    struct Foo {
        int iVal;
        friend ostream& operator << (ostream& os, const Foo& rhs) {
            os << rhs.iVal;
            return os;
        }
    };
}

int main() {
    // default constructed
    std::unordered_map<string, string> m1;
    printMap("m1", m1);

    // from initializer list
    std::unordered_map<string, string> m2 { {"One", "1"}, {"Two", "2"} };
    printMap("m2", m2);

    //copy constructor
    std::unordered_map<string, string> m3(m2);
    printMap("m3", m3);

    //move constructor
    std::unordered_map<string, string> m4(std::move(m1));
    printMap("m4", m4);

    // range constructor
    vector<std::pair<std::bitset<8>, int>> v {{0x12, 1}, {0x01, -1}};
    std::unordered_map<std::bitset<8>, int> m5(v.begin(), v.end());
    printMap("m5", m5);

    // custom key and equal
    std::unordered_map<Key, std::string, KeyHash, KeyEqual> m6 {
            {{"Rajat", "Girotra"}, "XII-A"},
            {{"Vidhu", "Ahuja"}, "XI-B"},
    };
    printMap("m6", m6);

    auto hash = [](const Foo& f) { return std::hash<int>{}(f.iVal); };
    auto pred = [](const Foo& lhs, const Foo& rhs) {
        return lhs.iVal == rhs.iVal;
    };
    std::unordered_map<Foo, double, decltype(hash), decltype(pred)> m7(10, hash, pred);
    m7.emplace(Foo{10}, 10.);
    printMap("m7", m7);
}