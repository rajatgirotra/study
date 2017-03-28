/*
 * A thread which already acquires a lock on a synchronized method, can call other synchronized methods
 * without getting blocked. But for this you must use boost::recursive_mutex.
 */
#include <iostream>
#include <string>
#include <fstream>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread/thread.hpp>
#include <boost/thread/locks.hpp>
#include <boost/thread/recursive_mutex.hpp>

using namespace std;
using namespace boost::posix_time;

class SynchronizeRecursive {
	//Self managing thread class.
	boost::thread* t;
	boost::recursive_mutex mtx;

	int counter;

	SynchronizeRecursive(const SynchronizeRecursive&);
	SynchronizeRecursive& operator = (const SynchronizeRecursive&);
public:
	SynchronizeRecursive() : counter(10) {
		t = new boost::thread(boost::ref(*this));
	}

	void f() {
		boost::lock_guard<boost::recursive_mutex> lg(mtx);
		cout << "f() with counter = " << counter << endl;
		--counter;
		if(counter > 0) {
			g();
		}
	}

	void g() {
		boost::lock_guard<boost::recursive_mutex> lg(mtx);
		cout << "g() with counter = " << counter << endl;
		--counter;
		if(counter > 0) {
			f();
		}
	}

	~SynchronizeRecursive() {
		if(t) {
			if(t->joinable())
				t->join();
			delete t;
		}
	}

	void operator() () {
		f();
        }

};


	

int main() {
        SynchronizeRecursive syncBlocked; 

	return 0;
}


