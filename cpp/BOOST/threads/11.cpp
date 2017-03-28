/*
A superb functionality is the provision of lock() and try_lock() functions which take 1 to 5 Lockable objects. The functions try to acquire lock on these Lockable objects, and will only return when
all locks are acquired. If any Lockable object throws an error, all the locks acquired are released. The order in which the parameters are specified is also not a problem. This function can be called
from different threads without fearing a deadlock. Let us now try.

This is a very good way of acquiring multiple mutexes atomically.

No matter how many times you run this program, you'll never see a deadlock. Very useful function to implement dining philosophers problem.
*/

#include <iostream>
#include <string>
#include <boost/thread/thread.hpp>
#include <boost/thread/locks.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
using namespace std;
using namespace boost;
using namespace boost::posix_time;

//Creating three mutex
boost::mutex m1, m2, m3;

void function(const string& str1, const string& str2) {
	lock(m1, m2, m3);

/*	lock_guard<boost::mutex> lg1(m1, adopt_lock_t());
	lock_guard<boost::mutex> lg2(m2, adopt_lock_t());
	lock_guard<boost::mutex> lg3(m3, adopt_lock_t()); */

	cout << str1 << " ";

	m1.unlock(); m2.unlock(); m3.unlock();
	boost::this_thread::sleep(seconds(1));	
	lock(m1, m2, m3);

	cout << str2 << endl;
	
	m1.unlock(); m2.unlock(); m3.unlock();
	boost::this_thread::sleep(seconds(1));	
}


int main() {

	boost::thread t1(&function, "A" , "B");
	boost::thread t2(&function, "X" , "Y");

	t1.join();
	t2.join();

	return 0;
}


/*

Similarly, the try_lock() function works. It returns -1, if all mutexes could be locked and otherwise returns the index of the Lockable object which could not be locked.

You also have lock(ForwardIterator first, ForwardIterator end) function which locks all mutexes in the range [first, end). The value_type of ForwardIterator must implement the Lockable concept
for this to work. Similar iterator exists for try_lock also.

*/
