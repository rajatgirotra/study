#include <iostream>
#include <string>

using namespace std;


string solution(string& S) {
    string formated_string = "";
    auto size = S.size();
    size_t digits = 0;
    for (auto ch : S) {
        if (ch >= '0' && ch <= '9')
            ++digits;
    }

    int count = 0;
    int mod = (digits % 3 == 0 ?  3 : 2);
    auto times = 0;
    if (digits % 3 == 1)
        times = 2;
    else if (digits % 3 == 2)
        times = 1;
    for (auto iter = S.crbegin(); iter != S.crend(); ++iter) {
        if (*iter >= '0' && *iter <= '9') {
            if (count > 0 && (count % mod == 0)) {
                --times;
                formated_string = "-" + formated_string;
                count = 0;
                if (times <= 0)
                    mod = 3;
            }
            formated_string =  string(1, *iter) + formated_string;
            ++count;
        }
    }
    return formated_string;
}
int main() {
    string s = "00-44  48 5555 - 8361";
    s = "0 - 22 1985--324";
    cout << solution(s) << endl;
    return 0;
}
