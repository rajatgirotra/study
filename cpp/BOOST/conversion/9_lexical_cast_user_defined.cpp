/*
We will now try to create a user defined type which can be used both as a source for lexical_cast.
For it we just need to overload the ostream operator.
*/

#include <iostream>
#include <string>
#include <boost/lexical_cast.hpp>
using namespace std;

class Employee {
private:
	string name;
	int empID;

public:
	Employee() : name(""), empID(-1)
	{ }

	Employee(const string& str, const int& id) : name(str), empID(id)
	{ }
	#if 0
	friend ostream& operator << (ostream& os, const Employee& e) {
		os << "Name: " << e.name << "   and    EmpID: " << e.empID << endl;
		return os;
	}
	#endif
};

int main() {
	Employee e1("Rajat", 148);
	cout << boost::lexical_cast<string>(e1);
	cout << (e1) << endl;
	cout << boost::lexical_cast<int>(e1);

	return 0;
}

