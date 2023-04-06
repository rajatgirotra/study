#include <algorithm>
#include <iostream>
#include <string>
#include <cctype>
using namespace std;

int main() {
    std::string input{};
    std::getline(cin, input);
    string camelCase{};
    bool underscore {false};
    for(auto i = 0u; i < input.size(); ++i) {
        if(input[i] == '_') {
            underscore = true;
            continue;
        }
//        char ch = (underscore || i == 0 ? static_cast<char>(std::toupper(input[i])) : input[i]); // Another variation to make the first character uppercase
        char ch = (underscore ? static_cast<char>(std::toupper(input[i])) : input[i]);
        camelCase.append(1, ch);
        underscore = false;
    }

    cout << "Camel case: " << camelCase << endl;
}