#include "serialize.hpp"
#include <iostream>

using namespace std;

int main() {
    cout << "hasSerialize<A>: " << std::boolalpha << hasSerialize<A>::value << endl;
    cout << "hasSerialize<B>: " << std::boolalpha << hasSerialize<B>::value << endl;
    cout << "hasSerialize<C>: " << std::boolalpha << hasSerialize<C>::value << endl;

    cout << "serialize<A>: " << serialize(A()) << endl;
    cout << "serialize<B>: " << serialize(B()) << endl;
    cout << "serialize<C>: " << serialize(C()) << endl;
}