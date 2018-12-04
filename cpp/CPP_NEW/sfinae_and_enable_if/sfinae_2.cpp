/*
 * Write a template function which return true if a template parameter type T has an embedded iterator type.
 * ie if T::iterator is valid, it should return true.
 */

#include <iostream>
#include <vector>
#include <string>
using namespace std;

// X::iterator is valid
struct X {
    struct iterator {};
};

// Y::iterator is invalid
struct Y {};

template <typename T>
struct has_iterator {
private:
    using true_type = char;
    struct false_type { true_type _[2]; };

    template <typename C>
    static false_type is_iterator(...);

    template <typename C>
    static true_type is_iterator(typename C::iterator*);

public:
    static constexpr bool value = (sizeof(is_iterator<T>(0)) == sizeof(true_type));
};

int main() {
    cout << "has_iterator<X>::value: " << std::boolalpha << has_iterator<X>::value << endl;
    cout << "has_iterator<Y>::value: " << std::boolalpha << has_iterator<Y>::value << endl;
    cout << "has_iterator<vector<string>>::value: " << std::boolalpha << has_iterator<vector<string>>::value << endl;
}