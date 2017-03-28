#include "5_pimpl_sample.h"
#include <iostream>
#include <string>
using namespace std;

struct pimpl_sample::impl
{
   impl()
   {
      cout << "Impl c'tor running" << endl;
   }

   ~impl()
   {
      cout << "Impl d'tor running" << endl;
   }

   string _s;
   void do_something_()
   {
      cout << _s << endl;
   }
};

pimpl_sample::pimpl_sample() : _pimpl(new impl)
//pimpl_sample::pimpl_sample() : _pimpl(new boost::scoped_ptr<impl>(new impl)) -->> A
{
   _pimpl->_s = "This is the pimpl idiom";
   //(*_pimpl)->_s = "This is the pimpl idiom";  ---> A
   throw 5; //throw an exception;
}

#if 1
pimpl_sample::~pimpl_sample()
{
   cout << "The pimpl_sample d'tor will not be called"<<endl;
//No need to destroy the _pimpl variable. It takes care of itself now.
}
#endif

void pimpl_sample::do_something()
{
   _pimpl->do_something_();
   //(*_pimpl)->do_something_(); --> A
}

