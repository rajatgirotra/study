Forcing MOVE SEMATICS

If we have a type Y and objects of this type a and b and we say

a = b;  then by default the classical implementation of assignment operator will be called.
But you know you can use move semantics if b is not used again or if b is used as a target in an expression.

So, we would like to convert b into an rvalue. The C++ standard provides a function.

template <typename T>
   std::move(const T& arg); to convert its argument to an rvalue, thereby forcing move sematics.

So if can say

  a = std::move(b); // to force move sematics.

The standard library function swap is also implemented like this.

template <typename T>
void swap(T& a, T& b) {
   T tmp(std::move(a));
   a = std::move(b);
   b = std::move(tmp);
}

Also using move sematics gives you the following advantages:

1] Performance boost:For those types that implement move sematics, most of thhe standard algorithms and 
operations will use move sematics and thus experience a performance gain.

2] We know that standard containers require its elements to implement copy semantics. i.e. elements should be
copyable. But it turns out that most of the times, simple movability is enough. So you can use types that are
movable  but not copyable. eg is: unique_pointer.

But there is one important thing that you need to take care of. When you say

a = std::move(b), we know that the object pointed by b is the one formerly pointed to by a. This resource should
be destroyed. But when does that happen. Only when b goes out of scope, or when b is used in a target expression
in which case the resource gets transferred again. So we are actually moving into a world on non-deterministic
destruction. But this is OK as far as the d'tor does not have any side-effects. But let say you have to release
a lock in a d'tor. Then there is no way of predicting when the lock might get released. So remember, if your
d'tor has any side-effects and you implement move semantics for your type, make sure you do any cleanup like
releasing the lock or any other thing in your move functions.
