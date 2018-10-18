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
    x = std::move(param); // BAD BAD BAD!! using std::move() with universal reference.
}