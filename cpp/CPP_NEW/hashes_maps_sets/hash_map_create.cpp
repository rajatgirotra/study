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
//    void printMap(const std::string& name, auto&& m) {
      template <typename T>
      void printMap(const std::string& name, T&& m) {
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

    // Inserting in a hash_map. There are so many API's to insert elements in a hashMap. Lets discuss

    /*
     * Insert
     * 1) std::pair<iterator, bool> insert(const value_type&);
     * 2) std::pair<iterator, bool> insert(value_type&&);
     * // true if element is inserted and iterator to that inserted element
     * // false if element could not be inserted and the iterator to the element which prevented the insertion
     *
     * 3) iterator insert(const iterator_hint, const value_type&);
     * 4) iterator insert(const iterator_hint, value_type&&);
     * return iterator is same as above. This one doesnt return bool so that it can be used with the insert_iterator like
     * other sequence and associative containers. The insert_iterator calls insert() and increments the returned iter.
     *
     * 5) void insert(InputIter first, InputIter last)
     * 6) void insert(std::initializer_list<value_type> list);
     */

    /* Emplace
     * template<typename... Args>
     * std::pair<iterator, bool> emplace(Args&&... args) --> Careful use of emplace will avoid any extra copy or move operations and create the
     * value_type directly inside the unordered_map memory.
     *
     * An important mention here is the example below.
     * hashMap.emplace(std::piecewise_construct, forward_as_tuple("DRW"), forward_as_tuple(10, "Rajat", "Girotra"));
     *
     * all arguments "std::piecewise_construct", and both forward_as_tuple() are sent to the std::pair constructor.
     * std::pair has this constructor which takes std::piecewise_construct. This constructor is used if both the first
     * and second elements need multiple arguments to their constructors.
     */

    /* emplace_hint
     * template <typename... Args>
     * iterator emplace_hint(const iterator_hint, Args&&...); // very trivial
     */

    /* try_emplace (only C++17 onwards)
     * template <typename... Args>
     * pair<iterator, bool> try_emplace(const key_type& k, Args&&... args) --> no-op if key already exists. Otherwise call's emplace(std::piecewise_construct, forward_as_tuple(k), forward_as_tuple(std::forward<Args>(args)...);
     * pair<iterator, bool> try_emplace(key_type&& k, Args&&... args) --> no-op if key already exists. Otherwise call's emplace(std::piecewise_construct, forward_as_tuple(std::move(k)), forward_as_tuple(std::forward<Args>(args)...);
     *
     * try_emplace() IS VERY HELPFUL WHEN INSERTING ELEMENTS IN HASH MAP WHICH HAS MOVE ONLY TYPES.
     * Lets create a HashMap of <string, std::unique_ptr<Foo>> and try to use emplace, insert, try_emplace. Then we should know better.
     * this function does not move from rvalue arguments if the insertion does not happen, which makes it easy to manipulate
     * maps whose values are move-only types. See try_emplace.cpp in this folder
     */

    /* reference& operator [] (const key_type& k)
     * reference& operator [] (key_type&& k)
     * returns a reference to the mapped_type for the given key. If key doesnt exist, then default constructs it; and then
     * returns a reference.
     */

    /* insert_or_assign
     * template <typename M>
     * std::pair<iterator, bool> insert_or_assign(const key_type& k, M&& obj);
     * std::pair<iterator, bool> insert_or_assign(key_type&& k, M&& obj);
     *
     * return true if insertion took place, false if assignment took place. If insertion took place, value_type is constructed
     * as value_type(k, std::forward<M>(obj)) or value_type(std::move(k), std::forward<M>(obj)) for second one.
     *
     * so basically insert_or_assign returns more information than operator[].
     */
    m7.emplace(Foo{10}, 10.);
    m7.insert({Foo{2}, 20.2});
    printMap("m7", m7);
}

/* see hash_map_insert.text next */
/* hash_map_movable_type.cpp next */
