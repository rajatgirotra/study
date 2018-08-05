The must important functions in allocator are:

1) allocate(num) --> ie allocate raw memory for "num" elements.
2) deallocate(p, num)  --> ie de-allocate raw memory for "num" elements starting at address p.
3) construct(p) --> initialize the raw memory at address p
4) destroy(p) --> destroy the element at address p

The default allocator (std::allocator<T>) is stateless, that is, all instances of the standard allocator are interchangeable, compare equal and can deallocate memory allocated by any other instance of the same allocator type.

ie 

std::vector<int> v;
std::list<int> l;

v.get_allocator() == l.get_allocator() is TRUE

Note that the standard libraries/container do not reference or use the allocators directly. The allocators are always used via allocator_traits<T>.
This means if you write your own custom allocator, you should either define a specicalization for alloctor_traits for your type or use the default one.

Example:

typename <typename T>
class MyCustomAllocator

typename<>
struct allocator_traits<MyCustomAllocator> {};

Let's look at the main interfaces of both allocator<> and allocator_traits<> together.
