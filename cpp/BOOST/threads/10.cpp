#include <iostream>
#include <boost/thread/thread.hpp>
#include <boost/thread/locks.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
using namespace std;
using namespace boost::posix_time;
using namespace boost;

boost::shared_mutex mtx;

struct callable {
	void operator() () {
		shared_lock<boost::shared_mutex> sl(mtx, boost::get_system_time() + seconds(4)); //This will time out as we have already acquired exclusive lock in main.
		if(!sl) {
			cout << "Could not acquire lock in thread" << endl;
			cout << "Owns Lock: " << boolalpha << sl.owns_lock() << endl;
			cout << "Mutex: " << sl.mutex() << endl;
		}
		else {
			cout << "Acquired lock in thread" << endl;
		}
	}
};

int main() {
		mtx.lock();
		//mtx.lock_shared();

		callable x;
		boost::thread newThread(x);


		newThread.join();
		cout << "Mutex in main thread: " << &mtx << endl;

		mtx.unlock();
		//mtx.unlock_shared();
		return 0;
}

/*
 * Also change mtx.lock() to mtx.lock_shared() and then see the difference.
 */
