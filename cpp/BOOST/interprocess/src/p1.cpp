#include <boost/interprocess/managed_shared_memory.hpp>
#include <iostream>
#include <cstdio>
#include <sstream>

using namespace std;

int main(int argc, char* argv[]) {
    using namespace boost::interprocess;
    if(argc==1) {
        //Remove shared memory on construction and destruction
        struct shm_remove
        {
            shm_remove() {  shared_memory_object::remove("MySharedMemory"); }
            ~shm_remove(){  shared_memory_object::remove("MySharedMemory"); }
        } remover;
        // parent
        managed_shared_memory segment(create_only, "MySharedMemory", 65536);
        auto size = segment.get_size();
        auto free_memory = segment.get_free_memory();
        cout << "SHM created, size: " << size << ", free_memory: " << free_memory << endl;

        auto ptr = segment.allocate(1024); //allocate 1KB
        cout << "SHM allocated 1KB at: " << ptr << ", size: " << segment.get_size() << ", free_memory: " << segment.get_free_memory() << endl;

        // get shm handle
        auto handle = segment.get_handle_from_address(ptr);
        std::stringstream s;
        s << argv[0] << " " << handle;
        s << std::ends;
        auto x = s.str();
        if(0 != std::system(x.c_str())) {
            return 1;
        }
        if(segment.get_free_memory() != free_memory) {
            return 1;
        }
    } else {
        managed_shared_memory segment(open_only, "MySharedMemory");
        managed_shared_memory::handle_t handle;
        std::stringstream s; s << argv[1]; s >> handle;

        void* msg = segment.get_address_from_handle(handle);
        cout << "SHM deallocating 1KB at: " << msg << std::endl;
        segment.deallocate(msg);
        cout << "SHM de-allocated, free_memory: " << segment.get_free_memory() << std::endl;
    }
    return 0;
}