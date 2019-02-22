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
        mValue = std::move(param);      ///  line A
    }
#endif

#if 0
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