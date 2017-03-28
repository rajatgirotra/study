/*
please read todelete.h first */

#include "deleter.h"
#include "todelete.h"

int main() {
	to_be_deleted* ptr = new to_be_deleted;
	
	deleter d;
	d.delete_it(ptr);

	return 0;
}

/*
Run the code using g++ deleter.cpp testdelete.cpp"
You'll notice that g++ gives you a warning that the type "to_be_deleted" is incomplete and its d'tor wont be called.
This is because in delete.h we have only made a forward declaration of class to_be_deleted
Also, in delete.cpp, you do not include "todelete.h" so the compiler is still not able to see its definition.
So it is an incomplete type and the compiler complains about it.
*/
