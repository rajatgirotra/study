Allocators are an abstraction for a memory model. Allocator objects deal with memory allocation and deallocation for a user defined type. If you look at STL containes, all of them use a default compiler provided allocator implementation.

template <typename T, typename Allocator=std::allocator<T>>
class vector {};

Writing your own allocator and plugging it in is as sample as

template <typename T>
class MySpecialAllocator;

vector<int, MySpecialAllocator<int>> xvector;

Let's look at the main allocator interface next.
