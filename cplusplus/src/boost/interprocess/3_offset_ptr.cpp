/*
 * boost interprocess provides an offset_ptr<> class which holds the offset(distance) between the offset_ptr<> object and the pointed to object.
 * offset_ptr<> allows you to store pointers on shared memory, otherwise it would not be possible for different process to share object pointers as they will be mapped to
 * different virtual addresses in their processes virtual tables.
 *
 * Let's use offset_ptr<> to store a linked list in ip::managed_shared_memory.
 * Read 7_shared_memory_object.cpp for storing raw pointers (given that all processes map the shared memory starting from the same virtual address).
 */
#include <boost/interprocess/managed_shared_memory.hpp>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <cassert>
#include <utility>

using namespace std;
namespace ip = boost::interprocess;

struct Node {
    int m_data;
    ip::offset_ptr<Node> m_next;

    Node(int data_arg = 0) : m_data(data_arg), m_next(nullptr) {}
};

int main(int argc, char** argv) {
    if(argc==1) {
        //i.e. if no argument given, assume this is parent. create managed_shared_memory and create a linked list of 10 nodes with values 1 to 10
        struct shm_remove {
            shm_remove() { ip::shared_memory_object().remove("MySharedMemory"); } // will ensure any stray shared memory object is destroyed.
            ~shm_remove() { ip::shared_memory_object().remove("MySharedMemory"); } // will ensure no stray shared memory object gets left behind.
        } remover;

        ip::managed_shared_memory segment(ip::create_only, "MySharedMemory", 65536); // 65536 bytes = 64KB
        auto free_memory = segment.get_free_memory();

        Node* prev {nullptr}, *current {nullptr}, *head {nullptr};

        for(int i = 1; i<= 10; ++i, prev = current) {
            current = static_cast<Node*>(segment.allocate(sizeof(Node)));
            current->m_data = i;
            current->m_next = nullptr;
            if(head == nullptr) {
                head = current;
            } else {
                prev->m_next = current;
            }
        }

        // now lets share head with another process.
        auto handle = segment.get_handle_from_address(head);
        stringstream s; s << argv[0] << " " << handle << ends;

        assert(std::system(s.str().data()) == 0);

        // remover will get destroyed and remove the shared memory, but lets make sure child has removed all named memory blocks.
        assert(free_memory == segment.get_free_memory());
    }
    else {
        // child process.
        // attach to the shared memory and get pointer and deallocate it.
        ip::managed_shared_memory segment(ip::open_only, "MySharedMemory");

        // get head ptr from handle
        ip::managed_shared_memory::handle_t handle;
        stringstream s; s << argv[1]; s >> handle;
        Node* head = static_cast<Node*>(segment.get_address_from_handle(handle));
        Node* prev {nullptr};
        while(head != 0) {
            prev = head;
            head = head->m_next.get();
            cout << "element: " << prev->m_data << endl;
            segment.deallocate(prev);
        }
    }
    return 0;
}

/*
 * Representing NULL with offset_ptr<>.
 * offset_ptr<> provides a pointer like interface. It is designed like a smart pointer so can work with STL containers also.
 * However representing nullptr is a bit complex. you know already that offset_ptr<> doesnt store a raw pointer. It store the distance (ptrdiff_t)
 * between its own address (i.e. this) and the pointed to address in the shared memory. Now if nullptr is address 0, then the distance between this and 0
 * will be different in each process.
 *
 * One way around this is to introduce a boolean variable in offset_ptr<> which tells if the offset_ptr<> is NULL or not. However this will hurt performance.
 * So the writers came up with something else. They said if offset_ptr<> distance is +1, it is assumed to be nullptr. this means offset_ptr<>
 * can never point to the address immediately after its this pointer. But this is not a big limitation.
 *
 * using namespace boost::interprocess;
 * offset_ptr<char> ptr;
 *
 * //Pointing to the next byte of it's own address
 * //marks the smart pointer as null.
 * ptr = (char*)&ptr + 1;
 * //ptr is equal to null
 * assert(!ptr);
 *
 * //This is the same as assigning the null value...
 * ptr = 0;
 * //ptr is also equal to null
 * assert(!ptr);
 */