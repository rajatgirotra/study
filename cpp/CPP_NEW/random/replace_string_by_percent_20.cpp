#include <iostream>
#include <cstring>
#include <string>
using namespace std;

namespace {
    string replace_space_with_percent_20(char* arg) {
        int space_count {};
        int len {};
        char* str = arg;
        while(*str != 0) {
            ++len;
            if(*str == ' ')
                ++space_count;
            ++str;
        }

        int newLength = len + space_count*2 + 1;
        char* newstr = new char[newLength];
        newstr[newLength-1] = 0;

        int k = newLength - 2;
        for(int i = len-1; i >= 0; --i) {
            if(arg[i] != ' ') {
                newstr[k--] = arg[i];
            } else {
                newstr[k--] = '0';
                newstr[k--] = '2';
                newstr[k--] = '%';
            }
        }
        string result(newstr);
        delete[] newstr;
        return result;
    }
}

int main() {
    cout << replace_space_with_percent_20("R a j a t") << endl;
}