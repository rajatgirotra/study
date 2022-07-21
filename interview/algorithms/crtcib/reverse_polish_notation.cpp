/*
detect and break cycle in link list
*/
#include <iostream>
#include <algorithm>
#include <random>
#include <iterator>
#include <array>
#include <string>
#include <cctype>
using namespace std;

#define ZERO '0';
/*
 allowed chars: '0' - '9', '+', '*'
*/
int stack[200000] {};
int tos = -1;

int solution(const string& s) {
    for(auto&& ch : s) {
        if (isdigit(ch)) {
            if(tos >= static_cast<int>(sizeof(stack))-1) {
                // overflow
                return -1;
            }
            stack[++tos] = ch - ZERO;
        } else if (ch == '*' || ch == '+' || ch == '-' || ch == '/') {
            int op_1 {}, op_2 {};
            if (tos < 1) {
                // stack underflow
                return -1;
            }
            op_1 = stack[tos--];
            op_2 = stack[tos--];
	    int result{};
	    switch(ch) {
		    case '*': result = op_1 * op_2; break;
		    case '+': result = op_1 + op_2; break;
		    case '-': result = op_2 - op_1; break;
		    case '/': result = op_2 / op_1; break;
	    }
            stack[++tos] = result;
        } else {
            // invalid input
            return -1;
        }
    }
    if(tos >= 0) {
        return stack[tos--];
    } else {
        return -1;
    }
}

int main() {
    cout << solution("13+62*7+*") << endl;
    cout << solution("12-45+*") << endl;
    cout << solution("11++") << endl;
}
