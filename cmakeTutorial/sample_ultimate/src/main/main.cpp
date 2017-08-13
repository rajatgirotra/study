#include "common/utils.hpp"
#include <iostream>
using namespace std;

int main() {
    bool b = wildcard_match("This expression could match from A and beyond.", "(A.*)");
    cout << boolalpha << b << endl;

    bool b1 = wildcard_match("As this string starts with A, does it match??.", "(A.*)");
    cout << boolalpha << b1 << endl;

    return 0;
}
