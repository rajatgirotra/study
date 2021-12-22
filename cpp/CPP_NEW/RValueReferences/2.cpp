//Demonstrating simple rvalue references by overloading copy c'tor.

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

class Number
{
private:
	static int counter;

public:
	char* poData;
	int tag;
	uint64_t size;
	Number(uint64_t arg = 1024*1024*1024*2ULL) : poData(new char[arg]), tag(++counter), size(arg)
	{
		cout << "Object created with tag: " << tag <<" ,poData: " << static_cast<void*>(poData) << endl;
	}

	~Number()
	{
		cout << "Object destroyed with tag: " << tag <<" ,poData: " << static_cast<void*>(poData)  << endl;
		if(poData)
		{
			delete[] poData;
			poData = 0;
		}
	}

	//Copy c'tor
	Number(const Number& rhs) : tag(++counter)
	{
		poData = new char[rhs.size];
		cout << "Copy of object created with tag: " << tag <<" ,poData: " << static_cast<void*>(poData) << " using tag: " << rhs.tag << endl;
	}

	//Move c'tor
	Number(Number&& rhs) : tag(++counter)
	{
		poData = rhs.poData;
		rhs.poData = nullptr;
		cout << "Move c'tor: object created with tag: " << tag <<" ,poData: " << static_cast<void*>(poData) << " using tag: " << rhs.tag << endl;

	}

	//Assignment Operator
	Number& operator = (const Number& rhs)
	{
		delete[] poData;
		this->poData = new char[rhs.size];
		cout << "Copy Assignment operator, this tag: " << this->tag <<" ,poData: " << static_cast<void*>(poData) << " ,incoming tag: " << rhs.tag << endl;
		return *this;
	}

	//Move Assignment operator
	Number& operator = (Number&& rhs)
	{
		cout << "Move Assignment operator, this tag: " << this->tag <<" ,poData: " << static_cast<void*>(poData)
			 << " ,incoming tag: " << rhs.tag << " ,incoming poData: " << static_cast<void*>(rhs.poData) << endl;
		std::swap(poData, rhs.poData);
        return *this;
	}
};

int Number::counter = 0;

Number foobar()
{
     Number n;
//     return std::move(n); // -Werror=pessimizing-move and -Wreturn-local-addr nice to include warning in your projects
     return n;

//    return Number();
}

int main()
{
//	Number n(foobar());
	Number n(std::move(foobar()));
	cout << "Hello World\n";
	return 0;
}

// You'll notice though that the move c'tor is not called. This is because of Return Value Optimization. The compiler sees that the
// only use of the local object in foobar() is to initialise the object n in main. So it basically just creates one object using 
// simple c'tor and assigns it to n. So no move semantics here.
// Read this beautiful article: http://definedbehavior.blogspot.in/2011/08/value-semantics-nrvo.html
// to force move semantics, explicitly use std::move() (line 76). However this is not recommended because it disables RVO.

// See line 70-72. If I create a local object and return it using std::move(). Is there any benefit I am getting???
/* Two things to note here.
 * The return type is Number not Number&&.
 * If return type was Number&&, it means you are returning a rvalue reference to a local object, i.e. returning a dangling reference
 * The second point is that return type Number is correct, so the function is anyway returning a rvalue. why do you want to move it??
 * Using move is just disabling RVO optimization again.
 */

