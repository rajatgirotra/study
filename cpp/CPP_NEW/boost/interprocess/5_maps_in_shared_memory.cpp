/*
 * Just like 4_vector_in_shared_memory.cpp, but maps also need a comparator function. Remember the declaration of map is
 *
 * template <typename Key,
 *           typename MappedValue,
 *           typename Compare = std::less<Key>,
 *           typename Allocator = std::allocator<std::pair<const Key, MappedValue>>>
 * class map;
 */
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/containers/map.hpp>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <cassert>
#include <utility>
#include <iterator>
#include <algorithm>

using namespace std;
namespace ip = boost::interprocess;

template <typename Key, typename MappedValue>
using ShmMemAllocator = ip::allocator<std::pair<const Key, MappedValue>, ip::managed_shared_memory::segment_manager>;

template <typename Key,
          typename MappedValue,
          typename Compare = std::less<Key>,
          typename Allocator = ShmMemAllocator<Key, MappedValue>>
using ShmMap = ip::map<Key, MappedValue, Compare, Allocator>;

using MySquareMap = ShmMap<int, int>;

int main(int argc, char** argv) {
    if (argc == 1) {
        // assume parent process, construct a map of <1, square of 1>, <2, square of 2> .. until <10, square of 10>
        struct shm_remove {
            shm_remove() { ip::shared_memory_object::remove("MySharedMemory"); }
            ~shm_remove() { ip::shared_memory_object::remove("MySharedMemory"); }
        } remover;

        ip::managed_shared_memory segment (ip::create_only, "MySharedMemory", 65536); // 64KB should be enough
        auto free_memory = segment.get_free_memory();

        ShmMemAllocator<int, int> alloc_inst (segment.get_segment_manager());
        MySquareMap* m = segment.construct<MySquareMap>("MySquareMap") (alloc_inst);
        // push back 1 to 10
        for(int i = 1; i <= 10; ++i) {
            m->insert(std::make_pair(i, i*i));
        }

        stringstream s;
        s << argv[0]; s << " dummy_arg" << ends;
        assert(std::system(s.str().data()) == 0);
        assert(free_memory = segment.get_free_memory());
        assert(segment.find<MySquareMap>("MySquareMap").first == nullptr);
    }
    else {
        // child process. Fetch MyVector and print it.
        ip::managed_shared_memory segment(ip::open_only, "MySharedMemory");
        MySquareMap* m = segment.find<MySquareMap>("MySquareMap").first;
        cout << "elements in map: " << m->size() << endl;
        for(auto&& item : *m) {
            cout << item.first << ": " << item.second << endl;
        }
        // destroy vector
        segment.destroy<MySquareMap>("MySquareMap");
    }
    return 0;
}

