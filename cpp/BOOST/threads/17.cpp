/*
template <typename T>
boost::thread_specific_ptr

Very simple: This class allows an application to have a separate instance of a data variable for each thread. It basically holds a pointer to data variable. 
Ver simple interface:

	c'tor
	thread_specific_ptr();
	thread_specific_ptr(void (*cleanupFunction)(T*)); //instead of calling delete p; when thread_specific_ptr goes out of scope, the user supplied function is used.

	T* get() ;
	T& operator * ();
	T* operator ->();
	T* release(); // thread_specific_ptr will release the underlying object and caller will be reposnible for cleanup.

	void reset(T* new_value = 0); //calls delete p; on the stored object and gets the new object to handle.
*/

#include <iostream>
#include <boost/thread/thread.hpp>
#include <boost/thread/thread_time.hpp>
#include <boost/thread/tss.hpp> //Note this include.
#include <boost/date_time/posix_time/posix_time.hpp>
#include <ctime>
#include <cstdlib>
using namespace std;
using namespace boost::posix_time;

struct callable {

	void operator() () {
		srand ( time(0) );

		boost::thread_specific_ptr<int> ptr;
		ptr.reset(new int(rand()));

		cout << "Integer: " << *ptr << endl;
	}
};

int main() {

	callable x;

	boost::thread threadOne(x);
	boost::this_thread::sleep(seconds(2));
	boost::thread threadTwo(x);

	threadOne.join();
	threadTwo.join();

	cout << boost::get_system_time() << endl; //get_system_time() returns nothing but ptime, which is typedef'ed to boost::system_time
							//Also note that it returns the UTC time, not the local time.

	return 0;
}
	

