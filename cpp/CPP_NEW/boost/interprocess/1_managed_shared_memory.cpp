/*
 * namespace ip = boost::interprocess;
 * ip::managed_shared_memory --> this class allows you to create shared memory of some size; and then allocate small blocks/chunks
 * from this shared memory (named or unnamed).
 *
 * unnamed shared memory segments --> the .allocate() function is used to get a chunk/block of whatever size you want.
 * the allocate() function returns you a pointer to the memory block. And since its a managed_shared_memory, boost will help keep track of this block.
 * the get_handle_from_address(ptr) function will return you an opaque handle_t, and you can use it in some other process to get
 * the block ptr again using the reverse get_address_from_handle(handle) function. Lets see this in action.
 */
#include <boost/interprocess/managed_shared_memory.hpp>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <cassert>

using namespace std;
namespace ip = boost::interprocess;

int main(int argc, char** argv) {
    if(argc==1) {
        //i.e if no argument given, assume this is parent. create managed_shared_memory and allocate a 1KB of memory
        struct shm_remove {
            shm_remove() { ip::shared_memory_object().remove("MySharedMemory"); } // will ensure any stray shared memory object is destroyed.
            ~shm_remove() { ip::shared_memory_object().remove("MySharedMemory"); } // will ensure no stray shared memory object gets left behind.
        } remover;

        ip::managed_shared_memory segment(ip::create_only, "MySharedMemory", 65536); // 65536 bytes = 64KB
        auto free_memory = segment.get_free_memory();
        void* block_ptr = segment.allocate(1024); // 1KB block
        assert(free_memory > segment.get_free_memory());
        cout << "free_memory before allocating 1KB block: " << free_memory << ", after: " << segment.get_free_memory() << endl;

        // get the handle to this block and pass as argument to child.
        auto handle = segment.get_handle_from_address(block_ptr);
        stringstream s{};
        s << argv[0] << " " << handle << ends;

        // call child process
        if(std::system(s.str().data()) != 0) {
            cerr << "Error in child process\n";
        }
        // remover will get destroyed and remove the shared memory, but lets make sure child has deallocated the block and size is as expected now.
        assert(free_memory == segment.get_free_memory());
    }
    else {
        // child process.
        // read handle from args
        ip::managed_shared_memory::handle_t handle {};
        stringstream s; s << argv[1]; s >> handle;

        // attach to the shared memory and get pointer and deallocate it.
        ip::managed_shared_memory segment(ip::open_only, "MySharedMemory");
        auto ptr = segment.get_address_from_handle(handle);
        segment.deallocate(ptr);
    }
    return 0;
}
