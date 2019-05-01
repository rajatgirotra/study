#include <iostream>
#include <string>
#include <cstring>
using namespace std;

#if 0
// uses strlen
void reverse_string(char* const str) {
    int len = strlen(str);
    for(int i = 0, j = len-1; i < j; ++i, --j) {
        char tmp = str[i];
        str[i] = str[j];
        str[j] = tmp;
    }
}
#endif

#if 1
// doesnt use strlen
void reverse_string(char* const arg) {
    char* str = arg;
    char* end = str;
    while(*end != 0)
        ++end;
    --end;
    while(str < end) {
        char tmp = *str;
        *str = *end;
        *end = tmp;
        ++str; --end;
    }
}
#endif

int main() {
    char name[] = "rajat";
    char name2[] = "abcdefghijklmnopqrstuvwxyz";
    reverse_string(name);
    reverse_string(name2);
    cout << "reverse_string(rajat): " << name  << endl;
    cout << "reverse_string(abcdefghijklmnopqrstuvwxyz): " << name2 << endl;
}