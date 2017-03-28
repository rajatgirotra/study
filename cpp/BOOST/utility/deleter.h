/*
Please read 3_*.cpp first 
We see here the actual problem with deleting an incomplete type
*/

#ifndef _DELETER_H_
#define _DELETER_H_

class to_be_deleted; //forward declaration

class deleter {
public:
	void delete_it(to_be_deleted* p);
};

#endif
