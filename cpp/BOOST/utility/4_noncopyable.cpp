/*
We already know that to disable copy c'tor and assignment operator, we can declare them as private within a class.
But a mush better approach is just to derive (PRIVATELY) from boost::noncopyable. this class defines private copy c'tor and assignment operator
which automatically disable copy c'tor and assignment operator for you class.

you should remember to derive PRIVATELY as the class boost::noncopyable does not need to establish any IS-A relation with your class.
this is obviously much better approach as it is clean & involves less typing.
*/

#include <iostream>
#include <boost/utility.hpp>
using namespace std;

class MyClass : private boost::noncopyable {
};

class ABC : public MyClass {
};

int main() {

	MyClass a;
	MyClass b(a); //Forbidded
	MyClass c;
	c = a; //Forbidded.

	ABC abc; //--> This is OK.
	ABC zyz(abc); // --> This is NOT OK.

	return 0;
}
