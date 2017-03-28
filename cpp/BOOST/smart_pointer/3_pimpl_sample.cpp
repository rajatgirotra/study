#include "2_pimpl_sample.h"
#include <iostream>
#include <string>
using namespace std;

struct pimpl_sample::impl
{
   string _s;
   void do_something_()
   {
      cout << _s << endl;
   }
};

pimpl_sample::pimpl_sample() : _pimpl(new impl)
{
   _pimpl->_s = "This is the pimpl idiom";
}

pimpl_sample::~pimpl_sample()
{
   if(_pimpl)
   {
      delete _pimpl; 
      _pimpl = 0;
   }
}

void pimpl_sample::do_something()
{
   _pimpl->do_something_();
}

