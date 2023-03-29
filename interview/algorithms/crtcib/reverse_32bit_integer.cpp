/*
write a function to reverse a 32 bit signed integer. if the reversed value doesnt lie in the 32 bit signed integer range (-2^31 to +2^31-1), return 0
*/

#include <iostream>
#include <cstdint>
#include <limits>
#include <cmath>
using namespace std;

/* we accept value as 64 bit so that larger values can fit in the argument,
   which when reversed, will give you value in the signed 32 bit range.
*/
int32_t reverse_integer(int64_t value) {
    const auto MAX = std::numeric_limits<int>::max();
    const auto MIN = std::numeric_limits<int>::min();
    int32_t res = 0;
    while(value != 0) {
        int digit = value % 10;
        if (res > MAX/10 || ((res == MAX/10) && digit > MAX%10 )) {
            return 0;
        }
        if (res < MIN/10 || ((res == MIN/10) && digit < MIN%10)) {
            return 0;
        }
        value /= 10;
        res = (res*10) + digit;
    }
    return res;
}

int main() {
    cout << "reverse 123: " << reverse_integer(123) << endl;
    cout << "reverse 2147483647: " << reverse_integer(2147483647) << endl;
    cout << "reverse 7463847412: " << reverse_integer(7463847412) << endl;
    cout << "reverse 8463847412: " << reverse_integer(8463847412) << endl;

    cout << "reverse -123: " << reverse_integer(-123) << endl;
    cout << "reverse -2147483647: " << reverse_integer(-2147483647) << endl;
    cout << "reverse -8463847412: " << reverse_integer(-8463847412) << endl;
    cout << "reverse -9463847412: " << reverse_integer(-9463847412) << endl;
}
