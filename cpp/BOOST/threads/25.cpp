/*
 * This program shows that for symchronization, you should be the lock_guar() lock type with all functions of the class.
 */

#include <iostream>
#include <string>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread/thread.hpp>
using namespace std;
using namespace boost::posix_time;

class AtomicityTest {
private:
	boost::thread* t;
	long val;
	mutable boost::mutex mtx;
	volatile bool bCancel;

public:
	AtomicityTest() : val(0), bCancel(false) {
		t = new boost::thread(boost::ref(*this));
	}

	~AtomicityTest() {
		if(t) {
			if(t->joinable())
				t->join();
			delete t;
		}
	}

	void cancel() {
		bCancel = true;
	}

	bool isCanceled() const {
		return bCancel;
	}

	long getValue() const {
		//boost::lock_guard<boost::mutex> lg(mtx);
		//By just uncommenting the above line, things work.
		return val;
	}

	void evenIncrement() {
		boost::lock_guard<boost::mutex> lg(mtx);
		++val;
		++val;
	}

	void operator() () {
		while(!isCanceled()) {
			evenIncrement();
		}
	}
};

int main() {
	AtomicityTest at;

	while(true) {
		long val = at.getValue();
		if(val % 2 != 0) {
			cout << "Value: " << val << " is NOT EVEN" << endl;
			at.cancel();
			break;
		}
	}
	return 0;
}
