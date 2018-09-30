#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/containers/string.hpp>
#include <boost/unordered_map.hpp>
#include <iostream>
#include <cstdint>
#include <utility>

using SegmentManager_t = ::boost::interprocess::managed_shared_memory::segment_manager;
using CharAllocator_t = ::boost::interprocess::allocator<char, SegmentManager_t>;
using ShmString_t = ::boost::container::basic_string<char, std::char_traits<char>, CharAllocator_t>;
using HashKey_t = ShmString_t;

struct OCGBroker {
    uint32_t mBrokerId;
    uint64_t mClientOrderIdSeed;
    uint64_t mClientOrderIdRunning;

    OCGBroker(uint32_t brokerId, uint64_t clientOrderIdSeed) : mBrokerId(brokerId),
                                                                 mClientOrderIdSeed(clientOrderIdSeed),
                                                                 mClientOrderIdRunning (clientOrderIdSeed) {}
};

using HashMapped_t = OCGBroker;
using HashValue_t = std::pair<const HashKey_t, HashMapped_t>;
using HashValueAllocator_t = ::boost::interprocess::allocator<HashValue_t, SegmentManager_t>;
using MyHashMap_t = boost::unordered_map<HashKey_t, HashMapped_t, boost::hash<HashKey_t>, std::equal_to<HashKey_t>,
        HashValueAllocator_t>;

using namespace std;


int main(int argc, char* argv[]) {
    if(argc > 1) {
        // connect to shared memory. Don't create one.
        ::boost::interprocess::managed_shared_memory segment(::boost::interprocess::open_only, "MySharedMemory");
        auto result = segment.find<MyHashMap_t>("MyMap");
        if(!result.first) {
            cout << "MyMap does not exist\n";
        } else {
            HashKey_t str("hkdealA", segment.get_allocator<HashKey_t>());
            auto it = result.first->find(str);
            if(it != result.first->end()) {
                cout << "broker details: " << it->second.mBrokerId << " " << it->second.mClientOrderIdSeed << " " << it->second.mClientOrderIdRunning << endl;
            }
        }
    } else {
        struct shm_remove {
            shm_remove() { ::boost::interprocess::shared_memory_object::remove("MySharedMemory"); }
            // ~shm_remove() { ::boost::interprocess::shared_memory_object::remove("MySharedMemory"); }
        } remover;

        ::boost::interprocess::managed_shared_memory segment(::boost::interprocess::open_or_create, "MySharedMemory", 65536);
        cout << "segment created, free memory: " << segment.get_free_memory();

        auto myMap = segment.construct<MyHashMap_t>("MyMap")(5, boost::hash<HashKey_t>(), std::equal_to<HashKey_t>(),
                segment.get_allocator<HashValue_t>());

        HashKey_t str("hkdealA", segment.get_allocator<HashKey_t>());
        HashMapped_t broker(1693, 20000001);
        myMap->insert(std::make_pair(str, broker));
    }
}
