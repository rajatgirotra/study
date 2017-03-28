#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <cstdint>
#include <cstdlib>
using namespace std;

int solution(string& S) {
    static const int32_t MIN_VALUE = 0;
    static const int32_t MAX_VALUE = (1<<20) - 1;

    std::stack<int32_t> stck;
    int pos = 0, nextpos = 0;
    bool end = false;
    while (true) {
        if (end)
            break;
        nextpos = S.find(" ", pos);
        if (nextpos == string::npos)
            end = true;
        string word = "";
        if (end == true)
            word = S.substr(pos);
        else
            word = S.substr(pos, (nextpos-pos));

        if (word == "DUP") {
            if (stck.empty())
                return -1;
            stck.push(stck.top());
        } else if (word == "POP") {
            if (stck.empty())
                return -1;
            stck.pop();
        } else if (word == "+") {
            if (stck.size() < 2)
                return -1;
            auto a = stck.top();
            stck.pop();
            auto b = stck.top();
            stck.pop();
            auto c = a + b;
            if (a < MIN_VALUE || a > MAX_VALUE)
                return -1;
            stck.push(c);
        } else if (word == "-") {
            if (stck.size() < 2)
                return -1;
            auto a = stck.top();
            stck.pop();
            auto b = stck.top();
            stck.pop();
            auto c = a - b;
            if (a < MIN_VALUE || a > MAX_VALUE)
                return -1;
            stck.push(c);
        } else {
            stck.push(atoi(word.data()));
        }
        pos = nextpos+1;
    }
    if (stck.empty())
        return -1;
    return stck.top();
}
int main() {
    string s = "13 DUP 4 POP 5 DUP + DUP + -";
    cout << solution(s) << endl;
    return 0;
}
