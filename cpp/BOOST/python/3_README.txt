About template class_
---------------------
class_ template class is used to GENERATE A PYTHON CLASS corresponding to type T.
It takes 3 other optional parameters (in any order).

template<T, Bases, HeldType, NonCopyable>

1) HeldType is the actual type held inside a python class wrapping a T instance when T's c'tor is called in python.
or when a T or T* is converted to Python. By default it is T, but can be a type derived from T, or a Dereferencable type
for which pointee<HeldType>::type is T or a class derived from T.
What is a typical use case when you would use a HeldType which is a type derived from T?? The best use case is when you want
to invoke a virtual function overriden in python from C++ side using a pointer to the base class.. Lets see an example and understand a few things. (See call_method.cpp)
 
