/*
solving the problem in 4_comparison.cpp using boost::Operators classes
*/
#include <iostream>
#include <string>
#include <boost/operators.hpp>
using namespace std;

class thing : private boost::less_than_comparable<thing>, private boost::equivalent<thing>
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

	if(a > b)
		cout << "a (Hello) is greater than b (Hell)" << endl;

	if(a <= b)
		cout << "a (Hello) is less than or equal to b" << endl;

	if( a == b ) //ie. a == b
		cout << "a (Hello) is equal to b (Hell) "<< endl;

	return 0;
}
