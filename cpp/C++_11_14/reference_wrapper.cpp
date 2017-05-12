#include <iostream>
#include <functional>
#include <string>
#include <utility>
#include <vector>
using namespace std;

void foo(const int& arg) {
    cout << "foo called with " << arg << endl;
}

int main() {
    int a = 10, b = 20;
    const int& x = a;
    //x = b; // Error. x is a const reference. cannot bind to another memory location.
    // But let say you want to wrap a reference and use it at some later point. Then??

    // Example:
    auto fo = std::bind(foo, x);
    // we change value of x 
    a = 100;
    fo(); // will foo be called with 10 or 100. it will be called with 10. But what if we want it to be called with 100. That is where reference_wrapper comes into picture. std::reference_wrapper allows you to wrap a reference in a copyable, assignable object. It is called a reference wrapper because if you look at its api, you'll see that the reference_wrapper is implicitly convertible to a reference. So you can use it anywhere you need to pass a reference as an argument. In reality it just holds a pointer to an object. Very trivial actually. It also provides an explicit get() api that returns a reference. See a very simple reference_wrapper implementation at the end of this file.  */

    auto fo1 = std::bind(foo, std::cref(x));
    a = 200;
    fo1(); // should be 200 now.

    // std::ref(x), and std::cref(x) are very simple wrapper functions. They return a reference_wrapper wrapping x.

    return 0;
}


/*

template <typename T>
struct reference_wrapper {
    private:
        T* _poPtr;

    public:
        reference_wrapper(const T& arg) : _poPtr(std::addressof(arg) {
        }

        reference_wrapper(T&&) = delete;

        reference_wrapper(const reference_wrapper& rhs) = default;
        reference_wrapper& operator = (const reference_wrapper& rhs) = default;

        // implicitly convertible to T&
        operator T& () const { return *_poPtr; }
        // explicitly convertible to T&
        T& get() const { return *_poPtr; }

        //In cases, where T is a function object or a function type, you can also
        // pass arguments straight to a reference_wrapper and the function will be called.
        template <typename... Args>
        std::result_of<somethingIneedtoLearn>::type
        operator() (Args&&... args) const {
            return std::invoke(get(), std::forward<Args>(args)...);
        }
};

*/
