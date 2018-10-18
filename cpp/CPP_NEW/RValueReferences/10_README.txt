Finally the definition of std::move is:

template <typename T>
typename remove_reference<T>::type&& 
std::move(T&& a) noexcept
{
    typedef typename remove_reference<T>::type&& RValueRef;
    return static_cast<RValueRef>(a);
}


If you keep forgetting the definitions of forward and move, just remember the following basics:

1) std::move() doesnt move anything
2) std::forward() doesnt forward anything.
They are pure casts, nothing else. They generate no executable code. And it's all at compile time. So there is no runtime
penalty also.

std::move() is unconditional cast. It will always casts its argument to rvalue, where-as std::forward is a conditional cast
It will only cast its argument to rvalue if the argument is an rvalue. Since std::move is unconditional, it is easier to now
think about its definition. Similarly for std::forward() you can work out the definition in your head now.

// unconditional move
template <typename T>
typename std::remove_reference<T>::type&& // unconditional return.
move(T&& arg) {
    using RValueRef = std::remove_reference<T>::type&&;
    return static_cast<RValueRef>(arg);
}


// conditional forward
template <typename T>
T&& forward(std::remove_reference<T>::type& arg) {
    return static_cast<T&&>(arg);

}