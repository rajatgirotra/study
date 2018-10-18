Universal vs rvalue references
==============================

Both have similar syntax, but by now you know how to differentiate between them.


example 1:
==========
void foo(Widget&&); // rvalue reference. foo() can only bind to rvalues

template <typename T>
void foo(T&&); //universal reference. foo() can bind to both const or non-const lvalues or rvalues; depending on the initializer.


example 2:
==========

Widget&& w = Widget(); // w is an rvalue reference

auto&& var = var2; // var is universal reference.

example 3:
=========
template<typename T>
void f(std::vector<T>&& param); //rvalue reference.