/*
 * Shows how to use condition_variable. Simple program where we repeatedly apply wax and then rub it on a car object.
 */

#include <iostream>
#include <string>
#include <boost/thread/thread.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread/locks.hpp>
#include <boost/thread/condition_variable.hpp>
using namespace std;
using namespace boost::posix_time;

class Car {
private:
	volatile bool waxOn;
	boost::condition_variable cond;
	boost::mutex mtx;
	typedef boost::unique_lock<boost::mutex> Lock;

public:
	Car() : waxOn(false) {
	}

	void waxed() {
		Lock lock(mtx);	
		waxOn = true;
		cond.notify_all();
	}

	void buffed() {
		Lock lock(mtx);	
		waxOn = false;
		cond.notify_all();
	}

	void waitForWaxing() {
		Lock lock(mtx);
		while(waxOn == false) {
			cond.wait(lock);
		}
	}

	void waitForBuffing() {
		Lock lock(mtx);
		while(waxOn == true) {
			cond.wait(lock);
		}
	}
};


class WaxOn {
private:
	boost::thread* t;
	Car& c;
	
	WaxOn(const WaxOn&);
	WaxOn& operator = (const WaxOn&);

public:
	WaxOn(Car& pCar) : c(pCar){
		t = new boost::thread(boost::ref(*this));
	}

	~WaxOn() {
		if(t) {
			if(t->joinable()) 
				t->join();
			delete t;
		}
	}

	void operator() () {
		try {
			while(!boost::this_thread::interruption_requested()) {
				cout << "Applying Wax" << endl;
				boost::this_thread::sleep(millisec(200));
				c.waxed();
				c.waitForBuffing();
			}
		} catch(const boost::thread_interrupted& e) {
			cout << "WaxOn task interrupted" << endl;
		}
	}

	void interrupt() {
		t->interrupt();
	}
};

class WaxOff {
private:
	boost::thread* t;
	Car& c;
	
	WaxOff(const WaxOff&);
	WaxOff& operator = (const WaxOff&);

public:
	WaxOff(Car& pCar) : c(pCar){
		t = new boost::thread(boost::ref(*this));
	}

	~WaxOff() {
		if(t) {
			if(t->joinable())
				t->join();
			delete t;
		}
	}

	void operator() () {
		try {
			while(!boost::this_thread::interruption_requested()) {
				c.waitForWaxing();
				cout << "Rubbing Wax" << endl;
				boost::this_thread::sleep(millisec(200));
				c.buffed();
			}
		} catch(const boost::thread_interrupted& e) {
			cout << "WaxOff task interrupted" << endl;
		}
	}

	void interrupt() {
		t->interrupt();	
	}
};


int main() {

	Car c;
	WaxOn waxOn(c);
	WaxOff waxOff(c);

	boost::this_thread::sleep(seconds(3));
	waxOn.interrupt();
	waxOff.interrupt();

	return 0;
}

