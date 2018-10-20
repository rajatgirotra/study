Remember that overloading a function taking a universal reference is almost always a bad idea.
So avoid it is you can. That's because function taking a universal reference can match much more argument types than you can imagine.

Example
=======

template <typename T>
void foo(T&& arg);

void foo(int arg); // overloaded


short s = 100;
foo(s); // will match the universal reference as that can produce an exact match. The foo() taking an int will require a
promotion of the argument.

But then if you have to use it anyway, then there are two possible ways of getting around it.

1) Tag dispatching
2) std::enable_if.

Let's see both of them in action next.
