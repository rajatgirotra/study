When to use std::move and when to use std::forward
==================================================

When you have an rvalue reference, example:

Widget(Widget&& rhs); // this means that rhs can only bind to an rvalue, ie it can always be moved. So always use std::move()
when using rvalue references.

When you have universal reference, it can bind to lvalue or rvalue both. So in that case, always use std::forward() which will
conditionally perform the correct cast depending on if the reference is initialized with lvalue or rvalue.

template <typename... Args>
void emplace_back(Args&&... args) {
    obj.emplace_back(std::forward<Args>(args)...);
}


WARNING
=======

template <typename T>
void foo(T&& param) {
    x = std::move(param); // BAD BAD BAD!! using std::move() with universal reference. Use std::forward<> instead.
}

Remember, ALWAYS when you create setter() functions in your classes always create them as taking universal references.

template <typename T>
void set(T&& arg);

instead of creating separate lvalue and rvalue overloads.

void set(const T& arg);
void set(T&& arg)

Because creating separate lvalue and rvalue overloads will have multiple disadvantages.
1) Biggest issue is scalability of design. If you have more than one arguments, then you have to create multiple overloads.
basically n arguments will call for 2^n overloads.

2) having separate overloads can result in reduced performance in certain cases. See 15.cpp for such an example.

3) There are always exceptions to this rule. Like std::vector<> has both lvalue and rvalue overloads for push_back().
This could be for a reason for let say if you decided to have a universal reference, then you would need to have a new template
parameter say U
template <typename U>
void push_back(U&& arg) --> This would have opened so many issues as you could call push_back(string) for an std:::vector<int>