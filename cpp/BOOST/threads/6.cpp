/*
See how lock_guard() is used to lock and unlock the mutex.
*/

#include <iostream>
#include <string>
#include <boost/thread/thread.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread/locks.hpp>
#include <boost/thread/mutex.hpp>
using namespace std;
using namespace boost;
using namespace boost::posix_time;

boost::mutex mtx; //Lockable mutex

void function(const string& str1, const string& str2) {
	while(!boost::this_thread::interruption_requested()) { //While thread is not interrupted
		//Call lock manually on mutex and then give ownership to lock_guard()
		mtx.lock();
		lock_guard<boost::mutex> lock(mtx, adopt_lock_t());
		cout << str1; 
		boost::this_thread::yield();
		cout << str2 << endl;
		boost::this_thread::yield();
	} //As the lock_guard() object is destroyed here, unlock() is called.
}

int main() {
	boost::thread threadOne(&function, "Hello", " World");
	boost::thread threadTwo(&function, "Cruel", " World");

	boost::this_thread::sleep(seconds(3));
	
	threadOne.interrupt();
	threadTwo.interrupt();

	threadOne.join();
	threadTwo.join();

	return 0;
}

/*
You can see that the output is always synchronized on the terminal. and the two strings are never intermixed. Remove the lock_guard() object creation
and then see the output again.
*/
