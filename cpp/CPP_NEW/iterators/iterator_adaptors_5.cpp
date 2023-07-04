/*
 * std::ostream_iterator: the c'tor takes an ostream object by reference and the overloaded =() operator writes to the stream.
 * std::istream_iterator: the c'tor takes an istream object by reference and the overloaded ++() and ++(int) operators read from the stream.

 * std::front_insert_iterator: the c'tor takes a container by reference and the overloaded =() operator calls push_front() on the container.
 * std::back_insert_iterator: the c'tor takes a container by reference and the overloaded =() operator calls push_back() on the container.
 * std::insert_iterator: the c'tor takes a container and an iterator and the overloaded =() operator calls insert() on the container.

 * std::move_iterator: the c'tor takes an iterator object and the overloaded *() operator calls std::move(*iter), ie the value is returned as an rvalue.
 * std::reverse_iterator: the c'tor takes an iterator object and provides capability to iterate in reverse order
 *
 * These are all examples of iterator adaptors. Let's see them in action. There are many convenient functions also to create
 * these iterators
 */

#include <iostream>
#include <string>
#include <iterator>
#include <ostream>
#include <istream>
#include <sstream>
#include <algorithm>
#include <deque>
#include <vector>
#include <set>
using namespace std;

int main() {
    istringstream iss("1 2 3 4 5");
    // Copy values from istringstream to an ostringstream
    ostringstream oss;
    std::copy(istream_iterator<char>(iss),
              istream_iterator<char>(),
              ostream_iterator<char>(oss, ", "));

    cout << "oss: " << oss.str() << endl;

    std::deque<double> deck;
    //push elements in the deck in the front
    double contents[] {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::copy(begin(contents), end(contents), front_inserter(deck));
    // print the deck
    for(auto&& item : deck) {
        cout << item << " ";
    }
    cout << endl;

    deck.clear();
    //push elements in the deck at the back.
    std::copy(begin(contents), end(contents), back_inserter(deck));
    // print the deck
    for(auto&& item : deck) {
        cout << item << " ";
    }
    cout << endl;

    deck.clear();
    //push elements in the deck using insert().
    std::copy(begin(contents), end(contents), inserter(deck, deck.begin()));
    // print the deck
    for(auto&& item : deck) {
        cout << item << " ";
    }
    cout << endl;

    // move iterator
    std::vector<string> v1{"Hello", "World"};
    std::vector<string> v2{"Goodbye", "cruel", "World"};
    //combine v1 and v2 into a set and empty v1 and v2.
    std::set<string> s1;
    cout << "v1 and V2 before\n";
    for(auto&& item : v1) {
        cout << item << ", ";
    }
    cout << "\n";
    for(auto&& item : v2) {
        cout << item << ", ";
    }
    cout << "\n";
    std::copy(make_move_iterator(v1.begin()), make_move_iterator(v1.end()), inserter(s1, s1.begin()));
    std::copy(make_move_iterator(v2.begin()), make_move_iterator(v2.end()), inserter(s1, s1.begin()));

    cout << "v1 and V2 and s1 after\n";
    for(auto&& item : v1) {
        cout << item << ", ";
    }
    cout << "\n";
    for(auto&& item : v2) {
        cout << item << ", ";
    }
    cout << "\n";
    for(auto&& item : s1) {
        cout << item << ", ";
    }
    cout << "\n";
    // Note how the item "World" remains in the v2 set as it is not moved. because it is already part of the set.
    // if we used a multiset, then this item would also be moved.

    return 0;
}

/*
 * Please read reverse_iterator_6.cpp next.
 */