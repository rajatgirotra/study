/*
 * a trivial class to store any variable type. int, float, string , user defined type. etc.
 * Interface is also trivial.
 *
 * std::any a = 16;
 * a = "Hello World"; // normal assignment works. old value is destroyed.
 *
 * std::any_cast<int>(obj); // to fetch the value. may throw std::bad_any_cast if you fetch wrong type.
 * has_value(); // return true/false if any holds a value or not
 * reset(); // empty the value
 * type(); return a typeinfo object. so obj.type() == typeid(int) comparisons can be done.
 */

#include <any>
#include <iostream>
#include <string>
#include <map>
#include <ostream>
#include <cassert>
using namespace std;

struct MyType {
    int m_i;
    int m_j;
    MyType(int arg1, int arg2) :  m_i(arg1), m_j(arg2) {}

    friend ostream& operator << (ostream& os, const MyType& rhs) {
        return os << "MyType(" << rhs.m_i << ", " << rhs.m_j << ")";
    }
};

int main() {
    std::any obj(12);
    obj = 16;
    obj.emplace<float>(100.5f); // can use emplace also
    obj = "Hello World";

    try {
        auto s = std::any_cast<std::string>(obj);
        cout << "any object has: " << s << endl;
    } catch(const std::bad_any_cast& e) {
        cout << "caught std::bad_any_cast: " << e.what() << endl;
    }

    try {
        auto i = std::any_cast<int>(obj);
        cout << "any object has: " << i << endl;
    } catch(const std::bad_any_cast& e) {
        cout << "caught std::bad_any_cast: " << e.what() << endl;
    }
    // There are more variations of std::any_cast<>. See below.

    obj.reset();
    if(!obj.has_value()) {
        cout << "std::any object is empty!\n";
    }

    std::map<std::string, std::any> myMap;
    myMap["integer"] = 10;
    myMap["string"] = std::string("Hello World");
    myMap["double"] = 67.4;

    for(auto&& [key, value] : myMap) {
        if(value.type() == typeid(int)) {
            cout << key << ": " << std::any_cast<int>(value) << endl;
        } else if (value.type() == typeid(double)) {
            cout << key << ": " << std::any_cast<double>(value) << endl;
        } else {
            cout << key << ": " << std::any_cast<std::string>(value) << endl;
        }
    }

    // default initialisation:
    std::any a;
    assert(!a.has_value());

    // initialisation with an object:
    std::any a2{10}; // int
    std::any a3{MyType{10, 11}};

    // inplace initialization, passing arguments of MyType ctor and std::any will ctor the MyType object directly in its storage.
    std::any a4{std::in_place_type<MyType>, 10, 11};

    // make_any
    std::any a6 = std::make_any<std::string>("Hello World"); // prefer this as it is easy to use and is same as in place construction above.
    // make_any<> returns std::any(std::in_place_type<T>, std::forward<Args>(args)...);

    // Note at statement B, MyType dtor is called first before std::any is reassigned a float value.
    std::any var = std::make_any<MyType>(10, 11);
    var = 100.0f;
    std::cout << std::any_cast<float>(var) << '\n'; // --> Statement B

    // std::any_cast<> variations.
    var = 10; // simple value 10 assigned to std::any

    // simple read std::any
    [[maybe_unused]] auto res = std::any_cast<int>(var);

    // read/write std::any. in this case the template argument is a reference.
    std::any_cast<int&>(var) = 100;
    cout << "after read/write through std::any_cast<int&>: " << std::any_cast<int>(var) << endl;

    // another way to read/write std::any. in this case the function argument is a pointer and returns a pointer to which you can assign a value.
    // the reason the function takes a pointer is same as for std::variant::get_if<>. the reason is so that you cannot give the function
    // an rvalue (i.e. a temporary), as then the function will return a pointer to a temporary which will get destroyed after the function call,
    // and you will be left with a dangling returned pointer.
    int* ptr = std::any_cast<int>(&var);
    *ptr = 150;
    cout << "after read/write through std::any_cast<int>(&var): " << std::any_cast<int>(var) << endl;

    /*
     * Most important is the cost associated with using std::any. std::optional<> and std::variant<> know precisely the types
     * it can hold. So their implementation do not do any extra heap allocation. But that's the not the case with std::any.
     * So std::any might do heap allocation. So it's costly. But when does it do heap allocation? ALWAYS?? NO: for small types,
     * it doesn't. Basically the standard says:
     *
     * Implementations should avoid the use of dynamically allocated memory for a small contained value. Example: where the
     * object constructed is holding only an int. Such small-object optimisation shall only be applied to types T for which
     * is_nothrow_move_constructible_v<T> is true. So to accommodate space for small types, the sizeof(std::any) itself is big.
     * print out for yourself.
     */
    cout << "sizeof(std::any): " << sizeof(std::any) << " bytes\n";
}
