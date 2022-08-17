/*
 * boost interprocess defines a concept of mappable_object.
 * classes like ip::shared_memory_object, ip::anonymous_shared_memory, ip::windows_shared_memory, ip::file_mapping etc
 * are examples of mappable_objects. These can have process/kernel/filesystem persistence as you read in 6_README.txt
 * These represent actual memory where you read/write data.
 *
 * then you have mapped_region class. mapped_region class can be used to map a region or full mappable_object into your process.
 * so the mapped_region c'tor takes as argument the mappable_object, the mode(read/write), the starting place in the mappable_object
 * which you want to map, and then finally the size of the region.
 * mapping_region::get_address() and ::get_size() is then used to get the base address and size of the mapped region where you can read/write.
 *
 * Also different processes which use mapping_region object to map to the same shared memory will off course get different virtual address mappings.
 * so mapping_region::get_address() will be different in different processes. This means you can not store and retrieve raw pointers in shared memory
 * as pointers always are virtual addresses. Imagine
 * 1) Process 1 uses "new" to allocate space on the shared memory and get a pointer back. This will be a virtual address. This virtual address
 *    is stored in the shared memory assuming Process 2 needs to access the data which has just been "new"ed.
 * 2) Process 2 cannot use the raw pointer as its virtual address space is totally different from Process 1.
 *
 * There are two ways around it.
 * 1) Boost.Interprocess gives you offset_ptr<> which you can store on shared_memory. This offset_ptr<> stores the distance from the actual
 *    address that has been "new"ed. So multiple processes can use offset_ptr<> safely. But code will be less efficient.
 *
 * 2) mapped_region API provides an option to specify the virtual address where you want to map a region. If multiple processes all use the same
 *    virtual address, then they can use raw pointers without any loss of efficiency.
 *
 *  For Point 2) above, CARE MUST BE TAKEN TO ALWAYS MAP REGIONS TO MULTIPLES OF PAGE SIZE FOR THAT OS. Otherwise the call could fail, or you
 *  could end up wasting a lot of page table addresses.
 *
 *  get PAGE TABLE SIZE using "static mapped_region::get_page_size() const" member function.
 *
 *  Limitations of C++ classes if you want them to store them on shared memory.
 *  1) Cannot have raw pointers. Use offset_ptr<> instead.
 *  2) Cannot use references as members of class
 *  3) Class cannot be virtual. as virtual table will be different in every process. So the VPTR will be different in each process.
 *  4) static data members will also be in different global address space in all processes. So modifying in one process will
 *     not change the value in the other process. Static members are not dangerous if they are just constant variables initialized when the process starts,
 *     and they don't change at all (for example, when used like enums) and their value is the same for all processes.
 */