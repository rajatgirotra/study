/* An std::shared_ptr is used to manage the lifetime of an object shared between multiple threads. Mutiple threads in a process can access the same resource using std::shared_ptr without worrying about how the resource will be deleted. shared_ptr class takes on that responsibility itself. As soon as the last shared_ptr<> object pointing to that resource goes out of scope, the object is destroyed. an std::shared_ptr<> class has size normally of 2 pointers. One pointer is of the type of the shared_ptr (template parameter first). The second pointer points to something called as a control block. The control block is the block where shared_ptr maintains multiple things.

1) Ref count : number of shared_ptr<> instances currently alive.
2) The custom deleter of functin pointer to call at destruction
3) weak_ptr count to remember how many weak pointers exist.
4) Other control block data.

cost of using shared_ptr is not less. We have the cost of
1) ref_counting: need to use atomic operations here.
2) virtual function call: used so that the object is properly destroyed even in the case when the base class d'tor is not declared virtual.
3) the control block size can increase with increase in their size.
4) Many more..
