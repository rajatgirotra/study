Finally the definition of std::move is:

template <typename T>
typename remove_reference<T>::type&& 
std::move(T&& a) noexcept
{
    typedef typename remove_reference<T>::type&& RValueRef;
    return static_cast<RValueRef>(a);
}
