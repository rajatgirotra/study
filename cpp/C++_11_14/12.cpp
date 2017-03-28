//Demonstrating simple rvalue references by overloading copy c'tor.

#include <iostream>
#include <string>
using namespace std;

class Number
{
private:
	static int counter;

public:
	double* poNumber;
	int tag;
	Number(const double& dArg = 6.6) : poNumber(new double(dArg)), tag(++counter)
	{
		cout << "Object created with tag: " << tag <<" ,poNumber: " << poNumber << " ,value: " << *poNumber << endl;
	}

	~Number()
	{
		cout << "Object destroyed with tag: " << tag <<" ,poNumber: " << poNumber << endl;
		if(poNumber)
		{
			delete poNumber;
			poNumber = 0;
		}
	}

	//Copy c'tor
	Number(const Number& rhs) : tag(++counter)
	{
		poNumber = new double(*rhs.poNumber);
		cout << "Copy of object created with tag: " << tag <<" ,poNumber: " << poNumber << " using tag: " << rhs.tag << endl;
	}

	//Move copy c'tor
	Number(Number&& rhs) : tag(++counter)
	{
		poNumber = rhs.poNumber;
		rhs.poNumber = 0;
		cout << "Move copy c'tor: object created with tag: " << tag <<" ,poNumber: " << poNumber << " using tag: " << rhs.tag << endl;
	}
};

int Number::counter = 0;

Number foobar()
{
        return Number(20);
}

int main()
{
	//Number n(foobar());
	Number n(std::move(foobar()));
	return 0;
}

// You'll notice though that the move copy c'tor is not called. This is because of Return Value Optimization. The compiler sees that the
// only use of the local object in foobar() is to initialise the object n in main. So it basically just creates one object using 
// simple c'tor and assigns it to n. So no move semantics here.
// Read this beautiful article: http://definedbehavior.blogspot.in/2011/08/value-semantics-nrvo.html
// We'll see later where the copy c'tor with move semantics can be used.

