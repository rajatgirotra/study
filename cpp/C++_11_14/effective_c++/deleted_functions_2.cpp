/* Even normal functions can be deleted. Also you can delete certain overloads based on type. For example, you only want a function to be called with an integer value, if called with char or bool, they should not be allowed. By default if you dont do anything, char, bool get implicitly get converted to int.

This is also the reason deleted functions take part in overload resolution. So that they get selected and if deleted, the compiler will give you an error.
 */

#include <iostream>
using namespace std;

bool is_lucky(int number) {
    return (number < 100 ? true : false);
}

bool is_lucky(char c) = delete;
bool is_lucky(bool c) = delete;
bool is_lucky(double c) = delete;

int main() {
    cout << "is_lucky(2): " << is_lucky(2) << endl;
    cout << "is_lucky(true): " << is_lucky(true) << endl;
    cout << "is_lucky('a'): " << is_lucky('a') << endl;
    cout << "is_lucky(12.3): " << is_lucky(12.3) << endl;

    return 0;
}

