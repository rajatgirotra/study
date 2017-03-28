Before we understand what the Perfect Forwarding problem is, lets look back at boost template metaprogramming and see how to
implement remove_reference<T> template metafunction.

remove_reference<int>::type                ------->          int
remove_reference<int const&>::type         ------->          int const
remove_reference<int&&>::type              ------->          int
remove_reference<int*>::type               ------->          int*
remove_reference<int*&>::type              ------->          int*  


Ok now the problem of perfect forwarding arised because of introduction of move semantics.

Let say you have the simple factory template function

template <typename T, template Arg>
shared_ptr<T> factory(Arg arg)
{
    shared_ptr<T> namedT(new T(arg));
    return namedT;
}

The above function has the following problem.

1) Clearly, arg is a value_type. So you create an extra copy of the object unnecessarily. NOT GOOD..!!

So you change the definition to

template <typename T, template Arg>
shared_ptr<T> factory(Arg& arg)
{
    shared_ptr<T> namedT(new T(arg));
    return namedT;
}

2) Again no Good.. Wont work for temporaries.. For eg:
factory(foobar());  //where foobar is "const Arg& foobar()"

So you introduce const Arg&
template <typename T, template Arg>
shared_ptr<T> factory(const Arg& arg)
{
    shared_ptr<T> namedT(new T(arg));
    return namedT;
}

3) Again No GOOD.. the problem now is that if the argument passed to factory() is an rvalue reeference, then
inside the factory method it will be treated as an lvalue (becuase it has a name), and we will be never be able
to call the move c'tor for T.

To solve this C++11 has introduced two new rules regarding rvalue references.

So the perfect forwarding problem is to forward the object in the same way is it received by the wrapper function factory(),
ie. to pass it as an lvalue if an lvalue is recieved or pass it as in rvalue if an rvalue is recieved.



