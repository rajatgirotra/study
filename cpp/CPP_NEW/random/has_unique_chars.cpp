/* function to check if a string has all unique characters
 */

#include <string>
#include <iostream>
using namespace std;

bool has_unique_chars(const std::string& s) {
    bool has_char[256] {};
    for (auto&& ch : s) {
        if(has_char[static_cast<int>(ch)])
            return false;
        has_char[static_cast<int>(ch)] = true;
    }
    return true;
}

int main() {
    cout << "has_unique_chars(Rajat): " << std::boolalpha << has_unique_chars("Rajat") << endl;
    cout << "has_unique_chars(abcdefghijklmnopqrtsuvwxyz): " << std::boolalpha << has_unique_chars("abcdefghijklmnopqrtsuvwxyz") <<endl;
}