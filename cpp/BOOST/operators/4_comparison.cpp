/*
Now lets define a class with operator<, so it can be used for storage in containers and sorting.
As you can see below, a user of a class who wants to perform the following operations will have to
use very confusing syntax.

1] testing if a is greater than b.
2] testing if a is less than or equal to b
3] testing if a is equal to b

*/
#include <iostream>
#include <string>
#include <boost/operators.hpp>
using namespace std;

class thing
{
	private:
		string name_;

	public:
		thing() { }
		explicit thing(const string& name) : name_(name) { }

		friend bool operator < (const thing& lhs, const thing& rhs)
		{
			return lhs.name_ < rhs.name_;
		}
};

int main()
{
	thing a("Hello");
	thing b("Hell");

	if(b < a)
		cout << "a (Hello) is greater than b (Hell)" << endl;

	if(! (b < a))
		cout << "a (Hello) is less than or equal to b" << endl;

	if( !(b<a) && !(a<b) ) //ie. a == b
		cout << "a (Hello) is equal to b (Hell) "<< endl;

	return 0;
}

/*
This is quite error-prone, so we just use operators use library and get away with implementing all operator ourselves.
*/
