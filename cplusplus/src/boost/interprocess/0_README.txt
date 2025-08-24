Let's understand the basics of Boost.Interprocess API. The API gives you "MANAGED" shared memory or memory mapped files or something similar to that.
What "MANAGED" means is that:
1. boost will keep track of how the shared memory/memory mapped file are created.
2. how to use it to construct objects/reserve space on them.
3. how to retrieve objects.
4. manage the free store. (the shared memory can get fragmented over time due to allocations and deallocations by the user).
5. destroy the shared memory or memory mapped file when you are done.

Let's look at the basic API.
namespace ip = boost::interprocess

1. create a managed_shared_memory.
ip::managed_shared_memory segment(ip::create_only, "MySharedMemory", SIZE_IN_BYTES);

2. Various API's to create/reserve space on it and get a handle to that space.
 a. Creating NAMED objects using a "construct<>" API.
    Every object or array of objects that is created is given a NAME. this name is sent to or already known to other processes which are using the same shared memory object. They can use the "find<>" API to get the pointer to that storage.

 b. Creating UNNAMED or anonymous objects.
    you can create objects without a name using the same "construct<>" API. find<> functions have no sense here, since anonymous objects have no name. We can only destroy the anonymous object via a pointer. So how to use them. You can use these together with a unique instance explained below. Basically get a pointer to an anonymous instance (maybe an array of some object type) and use "unique instance" construct to have a single pointer to the starting location of this vector.

 c. Creating unique objects.
   the api allows you to create "ONE AND ONLY ONE" unique object of any given type. Maybe you want to emulate some Singleton type across processes. this can be done using this construct. Since it is unique, you really don't need a name for this object. You can use the same "construct<>" and "find<>" api's to create a unique instance for any type. You can create several unique instances but each must be a different type.

 d. just get raw storage/raw bytes without an Object structure.
     you can just get raw storage/bytes in the shared memory using the "allocate" api. interprocess will just return you a pointer to the allocated bytes. To use it in another process, you will first need to get an opaque handle to this space using the "get_handle_from_ptr()" api. The handle can be stringified and sent to another/reader process. the reader process can then use "get_ptr_from_handle()" api to get the pointer back. It is obvious that different processes will load the same shared memory at different addresses in their private virtual tables, so sharing pointers to shared memory regions will simply not work.

================================================================================================================
How does boost::ip does all this. The most important thing in the boost implementation is a "segment_manager" class.
This is what manages the complete shared memory or memory managed file. Whenever you create a new shared memory of any size, boost::ip will silently construct a segment_manager object and place it at address 0 of the shared memory.
that is why the "get_free_memory()" on an empty shared memory always returns fewer bytes than the bytes specified in during construction.

What does the SegmentManager really do?
================================================================================================================
The layout of managed memory segment is shown below.
 _______ _________________
|       |         |       |
| some  | memory  | other |<- The memory algorithm considers
|members|algorithm|members|   "other members" as reserved memory, so
|_______|_________|_______|   it does not use it for dynamic allocation.
|_________________________|____________________________________________
|                         |                                            |
|    segment manager      |  The memory algorithm will return portions |
|                         |  of the rest of the segment.               |
|_________________________|____________________________________________|

The memory algorithm is the object that returns portions of that segment to users marking them as used and the user can return those portions to the memory algorithm so that the memory algorithm mark them as free again. So a memory algorithm has the same mission as malloc/free of standard C library, but it can only return portions of the segment where it is placed. the memory algorithm is also a configuration point because it defines two typedef's that you can use.

typedef /*implementation dependent*/ void_pointer;
typedef /*implementation dependent*/ mutex_family;

The void_pointer typedef defines the pointer type that will be used in this segment (by segment manager, allocators, containers). If the memory algorithm will be placed in a shared memory/mapped file mapped in different base addresses, this pointer type should be defined as an offset_ptr<void> or a similar relative pointer. If the memory algorithm will be used just within a process or using a fixed address mapping, void_pointer can be defined as void*.

The memory algorithm takes care of memory synchronizations, just like malloc/free guarantees that two threads can call malloc/free at the same time. If you are sure only one process will call construct/allocate, you can use a "null_mutex_family" object, otherwise use a "mutex_family" object.

Two memory algorithms already defined by boost are:

template<typename MutexFamily, typename VoidPointer>
class simple_seq_fit {
   // this class implements the simple sequential fit algorithm with a simply linked list of free buffers.
};

template<typename MutexFamily, typename VoidPointer>
class rbtree_best_fit {
   // this class implements an algorithm that stores the free nodes in a red-black tree to have logarithmic search/insert times.
};

The segment manager initializes the memory algorithm and tells this memory manager that it should not use the memory where the rest of the segment manager's member are placed for dynamic allocations (you see that depicted in the diagram above). The other members of the segment manager are a recursive mutex (defined by the memory algorithm's mutex_family::recursive_mutex typedef member), and two indexes (maps): one to implement named allocations, and another one to implement "unique instance" allocations. The memory needed to store these two indexes (maps) is also allocated by the memory algorithm

The first index is a map with a pointer to a c-string (the name of the named object) as a key and a structure with information of the dynamically allocated object (the most important being the address and the size of the object).
The second index is used to implement "unique instances" and is basically the same as the first index, but the name of the object comes from a typeid(T).name() operation.

As seen, the segment manager knows nothing about shared memory/memory mapped files. The segment manager itself does not allocate portions of the segment, it just asks the memory algorithm to allocate the needed memory from the rest of the segment. The segment manager is a class built above the memory algorithm that offers named object construction, unique instance constructions, and many other services..

It is defined as:
template<class CharType, class MemoryAlgorithm, template<class IndexConfig> class IndexType>
class segment_manager;
We specify the character type to be used to identify named objects, followed by the memory algorithm that will control dynamically the portions of the memory segment, and also the index type that will store the [name pointer, object information] mapping.
================================================================================================================
Ok, all this is good for allocating POD types on managed memory. But what about creating objects which can dynamically allocate memory, like std containers. example: vector could create memory dynamically. that memory should also be allocated on the managed memory. To make that possible, boost interprocess provides a special allocator which can be passed as the "Allocator" template parameter to these containers. The allocator objects are very simple. They store the segment_manager object and they always allocate memory on the managed object using the segment manager (via its memory algorithm). Example:

#include <boost/algorithm/allocator/allocator.hpp>
using namespace boost::interprocess;

using ShmemAllocator = allocator<double, managed_share_memory::segment_manager>;
using MyVector = std::vector<double, ShmemAllocator>;

managed_shared_memory segment(create_only, "MySharedMemory", 65536);
const ShmemAllocator alloc_inst(segment.get_segment_manager());
auto* ptr = segment.construct<MyVector>("MyVector")(alloc_inst);
================================================================================================================

