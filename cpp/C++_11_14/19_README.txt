Rule 1 regarding rvalue references is called Reference Collapsing rules.
According to this rule.

1) A& && collapses to A& (an rvalue reference to an lvalue references collapses to lvalue).
2) A&& & collapses to A& (an reference to an rvalue reference collapses to lvalue).
3) A& & collapses  to A& (a reference t a reference collapses to lvalue).
4) A&& && collapses  to A&& (an rvalue reference to an rvalue  collapses to rvalue).


Rule 2: The compiler has introduced a special template argument deduction rule for templte functions where
argument is an rvalue reference of the template parameter. ie. 

template <typename T>
void foo(T&& arg) {}

1) If T is an lvalue of type A, then T is deduced to be of type A&.
2) If T is an rvalue of type A, then T is deduced to be of type A.

So the perfect forwarding problem is now solved, if our factory method looks like:

template <typename T, typename A>
shared_ptr<T> factory(A&& arg)
{
    shared_ptr<T> namedT (new T(std::forward<A>(arg)));
    return namedT;
}

where std::forward is:

template <typename S>
S&& std::forward(typename remove_reference<S>::type& a) noexcept
{
    return static_cast<S&&>(a);
}


Lets see how.

We have:

X x; //lvalue
X foobar(); //rvalue

We are c'ting a type T (for example)

Then for lvalue x, we have

shared_ptr<T> factory(X& && arg)
{
    shared_ptr<T> namedT(new T(std::forward<X&> (x)));
    return namedT;
}

X& && std::forward(typename remove_reference<X&>::type& a) noexcept
{
    return static_cast<X& &&> (a);
}

which further boils down to:

shared_ptr<T> factory(X& arg)
{
    shared_ptr<T> namedT(new T(std::forward<X&> (x)));
    return namedT;
}

X& std::forward(typename remove_reference<X&>::type& a) noexcept
{
    return static_cast<X&> (a);
}


which is exactly what we want for an lvalue.

Now for rvalue we'll have:

shared_ptr<T> factory(X&& && arg)
{
    shared_ptr<T> namedT(new T(std::forward<X&&> (arg)));
    return namedT;
}

X&& && std::forward(typename remove_reference<X&&>::type& a) noexcept
{
    return static_cast<X&& &&> (a);
}

which further boils down to:

shared_ptr<T> factory(X&& arg)
{
    shared_ptr<T> namedT(new T(std::forward<X&&> (x)));
    return namedT;
}

X&& std::forward(typename remove_reference<X&&>::type& a) noexcept
{
    return static_cast<X&&> (a);
}

which is exactly what we want for an rvalue. So the main purpose of std::forward<> is to preserve the context: wheather the function
recieves an lvalue of rvalue.

If you really see carefully, we don't need the remove_reference<> at all. Because in both cases, the argument to std::forward
evaluates to an lvalue. You can substitute remove_reference<> with just S& and see that still both the cases work fine.
