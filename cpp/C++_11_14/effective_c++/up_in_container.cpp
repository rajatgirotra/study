#include <iostream>
#include <memory>
#include <vector>
using namespace std;

struct A {
    A() {
        cout << "A::A" << endl;
    };

    ~A() {
        cout << "~A::A" << endl;
    }

    A(const A&) {
        cout << "A(const A&)" << endl;
    }

    A& operator = (const A&) { 
        cout << "A& operator = (const A&)" << endl;
    }

    A(A&&) {
        cout << "A(A&&)" << endl;
    }

    A& operator = (A&&) {
        cout << "A& operator = (A&&)" << endl;
    }
};

template <typename T>
struct type_of {
    static constexpr auto value_of() {
        return "lvalue reference";
    };
};

template <typename T>
struct type_of<T&&> {
    static constexpr auto value_of() {
        return "rvalue reference";
    };
};

int main() {
    using VecOfUPtr_t = std::vector<std::unique_ptr<A>>;
    VecOfUPtr_t vec;
    /* std::make_unique signature is:
      template <typename T, typename... Args>
      std::unique_ptr<T> make_unique(Args&&... args) where args are forwarded to the constructor of type T. */
    auto x = std::make_unique<A>(); // here the unique_ptr(unique_ptr&&) c'tor is called.

    //auto y = x; // here the assignment operator is called. Since 'x' is an lvalue, the unique_ptr(const unique_ptr&) ctor is called which is implicitly deleted. So this expression is an error. */

    //vec.push_back(std::make_unique<A>()); // here the push_back(unique_ptr&&) is used which is OK.
    //vec.push_back(x); // Here the push_back(const unique_ptr&) function is used which is an error as the unique_ptr copy ctor is deleted.

    /* First see the signature of emplace_back 
     template <typename... Args>
     reference emplace_back(Args&&... args)
    ie it takes arguments needed to construct the type it holds. */
    vec.emplace_back(std::make_unique<A>()); // in this case, an std::unique_ptr<A> is passed to the c'tor so the move copy c'tor will be used.
    vec.emplace_back(); // Here no argument is passed, so unique_ptr c'tor is not passed any argument, ie class A c'tor is not passed any argument. */

    {
       // auto y = vec[0]; // trivial, copy c'tor is deleted.
        auto& y = vec[0]; // vec[0] returns a reference y is also a reference.
        auto&& z = vec[0]; // vec[0] returns a reference (lvalue) ie z is also an lvalue reference.
        auto&& w = std::move(vec[0]); // std::move returns an rvalue, so w here is an rvalue reference. Note no move 'ctor is called, w is just a reference still
        auto v = std::move(vec[0]); // now move c'tor is called.
        cout << "type_of y " << type_of<decltype(y)>::value_of() << endl;
        cout << "type_of z " << type_of<decltype(z)>::value_of() << endl;
        cout << "type_of w " << type_of<decltype(w)>::value_of() << endl;
        cout << "type_of v " << type_of<decltype(v)>::value_of() << endl;
    }
    cout << "y and z and w dont exist here, and since they are references nothing should be destroyed here" << endl;
    return 0;
}
