/*
  You can create blocks of Named objects in shared_memory using the managed_shared_memory::construct<> function
  and fetch these blocks in another process using the managed_shared_memory::find<> function.
 */
#include <boost/interprocess/managed_shared_memory.hpp>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <cassert>
#include <utility>

using namespace std;
namespace ip = boost::interprocess;

int main(int argc, char** argv) {
    using MyType = std::pair<double, int>;
    if(argc==1) {
        //i.e if no argument given, assume this is parent. create managed_shared_memory and allocate a 1KB of memory
        struct shm_remove {
            shm_remove() { ip::shared_memory_object().remove("MySharedMemory"); } // will ensure any stray shared memory object is destroyed.
            ~shm_remove() { ip::shared_memory_object().remove("MySharedMemory"); } // will ensure no stray shared memory object gets left behind.
        } remover;

        ip::managed_shared_memory segment(ip::create_only, "MySharedMemory", 65536); // 65536 bytes = 64KB
        auto free_memory = segment.get_free_memory();

        // construct a single MyType object and give a name
        auto ptr = segment.construct<MyType>("MyType object") (5.5, -99); // name followed by arguments to std::pair constructor
        // the function call operator is overloaded if you understand

        auto ptr2 = segment.construct<MyType>("MyType array")[10] (0.5, -1); // name followed by array size

        double double_array[] {-0.5, 0., 0.5};
        int int_array[] {100, 101, 102};
        auto ptr3 = segment.construct_it<MyType>("MyType array using iterator")[3] (&double_array[0], &int_array[0]);

        // call child process with any dummy argument
        stringstream s; s << argv[0] << " dummy_arg" << ends;
        if(std::system(s.str().data()) != 0) {
            cerr << "Error in child process\n";
        }
        // remover will get destroyed and remove the shared memory, but lets make sure child has removed all named memory blocks.
        assert(free_memory == segment.get_free_memory());
        auto res = segment.find<MyType>("MyType object");
        auto res2 = segment.find<MyType>("MyType array");
        auto res3 = segment.find<MyType>("MyType array using iterator");
        assert(!res.first && !res2.first && !res3.first); // first should be false as memory blocks are expected to be destroyed by now.
    }
    else {
        // child process.
        // attach to the shared memory and get pointer and deallocate it.
        ip::managed_shared_memory segment(ip::open_only, "MySharedMemory");

        std::pair<MyType*, ip::managed_shared_memory::size_type> res; // this is returned by find<>.
        res = segment.find<MyType>("MyType object");
        assert(res.first && res.second == 1);
        segment.destroy<MyType>("MyType object");

        res = segment.find<MyType>("MyType array");
        assert(res.first && res.second == 10);
        segment.destroy<MyType>("MyType array");

        res = segment.find<MyType>("MyType array using iterator");
        assert(res.first && res.second == 3);
        segment.destroy<MyType>("MyType array using iterator");
    }
    return 0;
}
