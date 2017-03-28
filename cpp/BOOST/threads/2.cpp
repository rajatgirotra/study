/*
Throwing anything other than thread_interrupted will call terminate() and exit your program.
*/

#include <iostream>
#include <boost/thread/thread.hpp>
#include <boost/thread/thread_time.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
using namespace std;
using namespace boost::posix_time;

struct callable {
	void operator () ();
};

void callable::operator() () {
	cout << "New Thread "<< endl;
	throw 5;
}	

int main() {

	try {
		callable x;
		boost::thread newThread(x);
		newThread.join();
	} catch(const int& e) {
		cout << "Integer Exception Caught" << endl;
	} 

	return 0;
}
	

