#include <iostream>
#include <boost/thread/thread.hpp>
#include <boost/thread/locks.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
using namespace std;
using namespace boost::posix_time;
using namespace boost;

boost::timed_mutex mtx;

struct callable {
	void operator() () {
		unique_lock<boost::timed_mutex> ul(mtx, boost::get_system_time() + seconds(5));
		if(!ul) {
			cout << "Could not acquire lock in thread" << endl;
			cout << "Owns Lock: " << boolalpha << ul.owns_lock() << endl;
			cout << "Mutex: " << ul.mutex() << endl;
		}
		else {
			cout << "Acquired lock in thread" << endl;
		}
	}
};

int main() {
		mtx.lock();

		callable x;
		boost::thread newThread(x);

		newThread.join();

		cout << "Mutex in main thread: " << &mtx << endl;

		mtx.unlock();
		return 0;
}
