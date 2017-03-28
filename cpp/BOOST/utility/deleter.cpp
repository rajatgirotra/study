/*
Please read deleter.h
*/

#include "deleter.h"
//#include "todelete.h"
#include <boost/checked_delete.hpp>


void deleter::delete_it(to_be_deleted* p) {
	delete p;
	//boost::checked_delete(p);
}

