/*
The implementation is not exception safe! The reason is that the pimpl_sample constructor may throw an exception after the pimpl has been constructed. Throwing an exception in the constructor implies that the object being constructed never fully existed, so its destructor isn't invoked when the stack is unwound. This state of affairs means that the memory allocated and referenced by the impl_ pointer will leak. However, there's an easy cure for this; scoped_ptr to the rescue!
*/

#ifndef _5_PIMPL_SAMPLE_
#define _5_PIMPL_SAMPLE_

#include <boost/scoped_ptr.hpp>

class pimpl_sample
{
private:
   struct impl; //forward declaration
   //impl* _pimpl;  //--> Note the difference in output if scoped_ptr<> is not used.
   boost::scoped_ptr<impl> _pimpl; //note the difference from 2_pimpl_sample.hpp
   //boost::scoped_ptr<impl>* _pimpl; ---> A

public:
   pimpl_sample();
   ~pimpl_sample();

   void do_something();
};

#endif
