/*
scoped_ptr and the pimpl idiom.
The idea behind the pimpl idiom is to insulate all clients from the knowledge about the private parts of a class. Because clients depend on the header file of a class, any changes to the header will affect clients, even if they are made to the private or protected sections. The pimpl idiom hides those details by putting private data and functions in a separate type defined in the implementation file and then forward declaring the type in the header file and storing a pointer to it. The constructor of the class allocates the pimpl type, and the destructor deallocates it. This removes the implementation dependencies from the header file. 

Looks very similar to the proxy pattern
*/

#ifndef _2_PIMPL_SAMPLE_
#define _2_PIMPL_SAMPLE_

class pimpl_sample
{
private:
   struct impl; //forward declaration
   impl* _pimpl;

public:
   pimpl_sample();
   ~pimpl_sample();

   void do_something();
};

#endif
