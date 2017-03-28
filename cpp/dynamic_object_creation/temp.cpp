#include <iostream>
#include <new>
using namespace std;

void* operator new(size_t sz) throw ()
{
	cout<<"Inside operator new(): size = "<<sz<<endl;
	return 0; //--> c'tor not called if you return 0;
}

void operator delete(void* ptr)
{
	cout<<"inside operator delete()"<<endl;
}

#if 0
void* operator new[](size_t sz) throw (bad_alloc)
{
	cout<<"Inside operator new[]: size = "<<sz<<endl;
	throw bad_alloc();
}
#endif

class A
{
public:
	A()
	{
		cout<<"A c'tor"<<endl;
	}
};


int main()
{
    try
    {
	A* ch = new A();
	//delete[] ch;
	A* chArr = new A[3];
	return 0;
    }catch(bad_alloc ex)
    {
        cout<<"Unable to allocate";
    }

}

