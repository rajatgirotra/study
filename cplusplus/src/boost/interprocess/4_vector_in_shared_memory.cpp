/*
 * you have already seen how to put POD data types in ip::managed_shared_memory (named and un-named).
 * you have also seen how to put pointers in shared memory using offset_ptr<>
 * But what about non POD data types, like vector, set, map?? They actually allocate more memory to store elements.
 * How do we store a vector object itself and the associated elements all on the shared memory.
 *
 * Boost interprocess libraries provides its own containers like vectors/maps/sets etc that we can use. All these container types
 * have Allocator template parameter. these Allocators manage the memory for elements in the containers. We have to use
 * managed_shared_memory::segment_manager which manages allocation/deallocation of container elements in the shared memory.
 *
 * Lets store a vector of ints in managed_shared_memory. Note that std::vector, std::map may/may not work, so lets stick to ip::vector and ip::map
 */
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/containers/vector.hpp>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <cassert>
#include <utility>
#include <iterator>
#include <algorithm>
#include <vector>

using namespace std;
namespace ip = boost::interprocess;

template <typename Key>
using ShmMemAllocator = ip::allocator<Key, ip::managed_shared_memory::segment_manager>;

template <typename Key>
//using ShmVector = ip::vector<Key, ShmMemAllocator<Key>>;
using ShmVector = std::vector<Key, ShmMemAllocator<Key>>; // both work.

using MyIntVector = ShmVector<int>;

int main(int argc, char** argv) {
    if (argc == 1) {
        // assume parent process, construct a vector of ints from 1 to 10
        struct shm_remove {
            shm_remove() { ip::shared_memory_object::remove("MySharedMemory"); }
            ~shm_remove() { ip::shared_memory_object::remove("MySharedMemory"); }
        } remover;

        auto segment = ip::managed_shared_memory(ip::create_only, "MySharedMemory", 65536); // 64KB should be enough
        auto free_memory = segment.get_free_memory();

        MyIntVector* vec{};
        {
            ShmMemAllocator<int> allocator (segment.get_segment_manager()); // segment_manager is copyable.
            vec = segment.construct<MyIntVector>("MyIntVector")(allocator);
        }

        // push back 1 to 10
        for(int i = 1; i <= 10; ++i) {
            vec->emplace_back(i);
        }

        stringstream s;
        s << argv[0]; s << " dummy_arg" << ends;
        assert(std::system(s.str().data()) == 0);
        assert(free_memory == segment.get_free_memory());
        assert(segment.find<MyIntVector>("MyIntVector").first == nullptr);
    }
    else {
        // child process. Fetch MyVector and print it.
        ip::managed_shared_memory segment(ip::open_only, "MySharedMemory");
        MyIntVector* vec = segment.find<MyIntVector>("MyIntVector").first;
        cout << "elements in vector in reverse order: ";
        std::copy(vec->crbegin(), vec->crend(), ostream_iterator<int>(cout, " " ));

        // destroy vector
        segment.destroy<MyIntVector>("MyIntVector");
    }
    return 0;
}