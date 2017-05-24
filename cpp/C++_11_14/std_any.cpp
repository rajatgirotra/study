/* std::any or boost::any is a very simple concept. It is a NON template class with a template c'tor.
It stores two things, a value and the type of the value. Then later to retreive the value you can use any_cast<> function.
This function will throw an exception if the contained value cannot be converted to the requested type. 
something like:

class Any {
private:
    const std::type_info& type_detail;
    char* data;

public:
    template <typename ValueType>
    Any(ValueType&& value) : type_detail(typeid(ValueType)) {
        data = new char[sizeof(ValueType)];
    }

    ~Any() {
        delete[] data;
    }

    const std::type_info& type() const {
        return type_detail;
    }
};

In reality, we don't store data in a void pointer (or char pointer). If you look at the definition of boost::any, it is slighlty complex but worth understanding. It has nested class placeholder and holder, where holder is derived from placefolder.

class Any {

    placeholder* content;

    Any(const ValueType& v) : content(new holder(v)) {
    }

    struct placeholder {
        virtual ~placeholder() {}
        
        virtual placeholder* clone() = 0;
    };
   
    template <typename ValueType>
    class holder : public placeholder {
        ValueType held;

        public:
            holder(const ValueType* arg) : held(arg) {}
            holder(ValueType&& arg) : held(static_cast<ValueType&&>(arg)) {}

            placeholder* clone() {
                return new holder(held);
            }
    };
}
*/

#include <iostream>
#include <string>
#include <functional>
#include <any>  // check your compiler supports std::any
#include <vector>
using namespace std;

class UDO {}; // some User Defined Object

int main() {
    std::vector<std::any> anyList;
    anyList.emplace(std::any(1));  // std::any is int
    anyList.emplace(std::any(std::string("HelloWorld")));  // std::any is string
    char name[] = "Rajat";
    anyList.emplace(std::any(name));  // std::any is char* (decayed type is stored)
    anyList.emplace(std::any(UDO()));  // std::any is UDO
    anyList.emplace(std::any(87.5));  // std::any is double

    try {
        auto i = std::any_cast<int>(anyList[0]);
        cout << "std::any int is: " << i << endl;
    } catch(const std::bad_any_cast& e) {
        cerr << "Caught exception when fetching an int: " << e.what() << endl;
    }
    return 0;
}

            
    

