/* Very good read to clear your concepts.
Problem: There is a library which provides a function called "register_callback". This takes a function pointer and calls the function at some later time. You need to create a function call logger, so that whenever the given library makes a callback, you log 
1) The callback name (the callback function name is also passed to the register_callback function)
2) The arguments
3) The result of the callback.

Solution
--------
1) Bad solution: You can go ahead and modify every callback function to log the function name, arguments and result from within the callback function itself. Very bad. Think when you have multiple return statements in your callback.

2) Good solution: For every callback function you need to register, create a logger template which takes the callback function as a template parameter and the callback function name also as a template parameter. Then register this function as a callback with the library, instead of the real function. When you logger function is called, cout the function name, arguments, and call the actual back and log the result. Note that this is trickier as the callback signature is not same.

Let's get started.
*/

#include <iostream>
#include <vector>
using namespace std;

static constexpr const char cbname[] = "my_callback"; // my callback function name to be logged.

// F is a function pointer type, f is the actual pointer to function, name is the callback function name
template<typename F, F f, const char* name>
struct fn_logger;

// really if you think, we need the return type and the arguments of the function pointer, so we need a partial specialization of the fn_logger class and the arguments can be as many so we need a variadic template for logging args. Lets write that first
template <typename... Args>
void log_args(Args&&... args) {
    (cout <<  ... << args) << endl; //easiset way to out a parameter pack in C++17.
}

// Need to partial specialize fn_logger to get the return type, arguments, and the actual function pointer.
template<typename R, typename... Args, R(*f)(Args...), const char* name>
struct fn_logger<R(*)(Args...),  f, name> {
    static R call(Args&&... args) {
       cout << "callback function name: " << name << endl;
       cout << "arguments: ";
       log_args(std::forward<Args>(args)...);
       auto result = f(std::forward<Args>(args)...);
       cout << "Result: " << result << endl;
    }
};

template<typename F, F f, const char* name>
static constexpr auto logger = fn_logger<F, f, name>::call;

int foo1(double d) {
  cout << "foo1 called with double: " << d << endl;
  return -99;
} 

int foo2(std::vector<int> v) {
  cout << "foo2 called with std::vector<int>: " << endl;
} 

auto fpfoo1 = &foo1;
auto fpfoo2 = &foo2;


namespace library {
    template <typename SomeCallable>
    void register_callback(SomeCallable&& callback, const char* cbname) {
    }
}

int main() {
    logger<decltype(fpfoo1), foo1, cbname>(10);
    return 0;
}
