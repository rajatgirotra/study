/*
Please read Must_Read_2.txt

We start of by deriving from the equivalent class in the Operators library. You dont need to use public inheritance, private inheritance works just as well.
include boost/operators.hpp.
*/

#include <boost/operators.hpp>
#include <iostream>
using namespace std;

class some_class : private boost::equivalent<some_class>
{
	private:
		int _value;
	public:
		some_class(int value) : _value(value) {}

		bool less_than(const some_class& rhs) const
		{
			return _value < rhs._value;
		}
};

bool operator < (const some_class& lhs, const some_class& rhs)
{
	return lhs.less_than(rhs);
}

int main()
{
	some_class s1(12);
	some_class s2(11);

	if(s1 == s2)
		cout << "s1 == s2" << endl;
	else
		cout << "s1 != s2" << endl;

	return 0;
}


