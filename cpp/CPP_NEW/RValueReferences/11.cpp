/* When would returning by RValue Reference be a good idea??
   It will be a good idea when you want to invoke the function on a temporary object. Example:
   */

#include <iostream>
#include <string>

using namespace std;

class Connection {
    std::string mValue;
public:
    Connection(std::string value) : mValue(std::move(value)) {};

    const std::string& getValue() const & {
        return mValue;
    }
    std::string&& getValue() && {
        return std::move(mValue);
    }
};

int main() {
    // here Connection() object is a temporary (an rvalue), so to get the underlying resource, we
    // can have function which returns by rvalue reference. But we make sure we use the "&&" ref qualifier
    // to make sure our version is invoked for only rvalue objects, not for l-value objects.

    // but a breakpoint in getValue() functions to see which getValue gets called,
    // you'll notice it break at line 19.
    auto x = Connection("Hello World").getValue();
    cout << x << endl;
}