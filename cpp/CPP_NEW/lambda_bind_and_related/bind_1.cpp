/*
template <typename F, typename... Args>
<someFunctionObject> bind(F&& f, Args&&... args)

std::bind is a function which takes any c++ callable, and associated args, and returns a function object (function wrapper)
which wraps F and the arguments Args. this function object can be called later using the function call operator.

std::is_bind_expression<T>::value == true where T is type of someFunctionObjectType

What are callables?
 1) normal function
 2) function pointer
 3) function object
 4) lambda
 5) class member function
 6) member function pointer
 7) class member data

When F is a 5,6,7 above, the second argument must be an object of the class or a pointer (including smart pointers like std::unique_ptr,
 std::shared_ptr) to it.

Arguments Args... are always copied or moved into the function object, and whenever the someFunctionObject() is called, it is passed by value
 unless the arguments used to call std::bind() was std::ref() or std::cref().

What can be the arguments to std::bind()?
 1) normal variables
 2) std::cref(), std::ref()
 3) a nested std::bind() expression. in this case, the nested std::bind operation is invoked greedely and its value is passed to the outer bind function.
 4) std::placeholders::_1, _2 etc --> These are placeholder types and there values are substituted at the time the function object is called.
*/

#include <random>
#include <iostream>
#include <memory>
#include <functional>

using namespace std;

void f(int n1, int n2, int n3, const int& n4, int n5)
{
    std::cout << n1 << ' ' << n2 << ' ' << n3 << ' ' << n4 << ' ' << n5 << '\n';
}
 
int g(int n1)
{
    return n1;
}
 
struct Foo {
    void print_sum(int n1, int n2)
    {
        std::cout << n1+n2 << '\n';
    }
    int data = 10;
};
 
int main()
{
    using namespace std::placeholders;  // for _1, _2, _3...
    // _1, _2, _3 are all types.
 
    // demonstrates argument reordering and pass-by-reference
    int n = 7;
    // (_1 and _2 are from std::placeholders, and represent future
    // arguments that will be passed to f1)
    auto f1 = std::bind(f, _2, _1, 42, std::cref(n), n);
    n = 10;
    f1(1, 2, 1001); // 1 is bound by _1, 2 is bound by _2, 1001 is unused
                    // makes a call to f(2, 1, 42, n, 7)
    // note the usage of std::cref(n) and n. Simply specifying n, binds the value of n at the time the std::bind expression is specified. using std::cref(n), means, the value of n will be decided at invocation time.
 
    // nested bind subexpressions share the placeholders
    auto f2 = std::bind(f, _3, std::bind(g, _3), _3, 4, 5);
    f2(10, 11, 12);
 
    // common use case: binding a RNG with a distribution
    std::default_random_engine e;
    std::uniform_int_distribution<> d(0, 10);
    std::function<int()> rnd = std::bind(d, e); // a copy of e is stored in rnd
    for(int x=0; x<10; ++x)
        std::cout << rnd() << ' ';
    std::cout << '\n';
 
    // bind to a pointer to member function
    Foo foo;
    // When the callable is a pointer to a non static member function or to member data, the first
    // argument must be a pointer, reference or smart pointer of the that class.
    auto f3 = std::bind(&Foo::print_sum, &foo, 95, _1);
    f3(5);
 
    // bind to a pointer to data member
    auto f4 = std::bind(&Foo::data, _1);
    std::cout << f4(foo) << '\n';

    auto f5 = std::bind(&Foo::data, foo);
    std::cout << f5() << '\n';

    bool is_bind_expr_f4 = std::is_bind_expression<decltype(f4)>::value;
    cout << "is_bind_expr_f4: " << is_bind_expr_f4 << endl;
 
    // smart pointers can be used to call members of the referenced objects, too
    std::cout << f4(std::make_shared<Foo>(foo)) << '\n'
              << f4(std::make_unique<Foo>(foo)) << '\n';
}

/* Internally, std::bind make use of std::invoke(). Again std::invoke() is also very similar

template <typename F, typename... Args>
std::invoke_result_t<F, Args...> bind(F&& f, Args&&... args)

It takes a callable, and corresponding args and immediately invokes f with arguments as args.

for std::invoke(f, t1, t2, ..., tN), it does the following:
1) if f is a pointer to non static member function of some class T, then the call is:
   (*t1.f)(t2, t3, ... tN)

2) Otherwise the call is like: f(t1, t2, t3, ..., tN)

its very good to understand std::invoke, but before that you'll need to be thorough with the following concepts:

1) std::cref
2) std::reference_wrapper
3) decltype(auto) return type.
4) std::forward
5) constexpr
6) std::is_member_function_pointer
7) Other functional programming (mostly understanding type_traits)
*/

