#include <iostream>
#include <string>
using namespace std;

/* Predict, what will be template parameter type T when we use the universal reference setName() function and what
 * string constructor will be called at line A.
 *
 * Also if we replace the universal reference version with separate lvalue and rvalue overloads, what functions in the string
 * class will be called.
 */

class Widget {
private:
    std::string mValue;
public:
#if 1
    template <typename T>
    void setName(T&& param) {
        mValue = std::move(param);      ///  line A (answer is std::string copy assignment operator which takes const char* argument).
        // but really we should use std::forward() here as argument is universal reference.
    }
#endif

#if 0
// if we enable this part, then compiler will try to convert argument "RajatGirotra" which is const char(&)[13] to string using the string constructor
// a temporary string will be constructed and then the r-value overload will be called, which will call string's move assignment operator.
    void setName(std::string&& param) {
        mValue = std::move(param);
    }

    void setName(const std::string& param) {
        mValue = param;
    }
#endif
};

int main() {
    Widget w;
    w.setName("RajatGirotra");
    return 0;
}