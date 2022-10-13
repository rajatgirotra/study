// Write a program to replace all spaces in a string with %20

#include <iostream>
#include <algorithm>
#include <random>
#include <iterator>
#include <limits>
#include <iomanip>
#include <cstring>
using namespace std;

// true length is length of string with spaces. 
// but assume that str array is big enough to allocate %20 + null character.
void urlify(char str[], int trueLength, int spaces) {
    auto index = trueLength + (spaces * 2);
    str[index--] = 0;
    for(int i = trueLength-1; i >=0; --i) {
        if(str[i] == ' ') {
            str[index--] = '0';
            str[index--] = '2';
            str[index--] = '%';
        } else {
            str[index--] = str[i];
        }
    }
}

int main() {
    string str {"http://www.google.com/Search Query Goes Here"};
    int spaces {};
    int start_pos {}, found_pos{};
    while(true) {
        found_pos = str.find(' ', start_pos);
        if(found_pos == string::npos) {
            break;
        } else {
            ++spaces;
            start_pos = found_pos + 1;
        }
    }
    auto new_size = str.size() + (spaces * 2) + 1;
    char url_str[new_size] {}; // +1 for null character
    strncpy(url_str, str.data(), str.size());
    urlify(url_str, str.size(), spaces);
    cout << "URLify string: " << url_str << endl;
}