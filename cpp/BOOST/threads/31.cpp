/*
 * Please read CheckZero.java first
 * Create two Runnables, one with a run( ) that starts and calls wait( ). The second class should capture the reference of 
 * the first Runnable object. Its run( ) should call notifyAll( ) for the first task after some number of seconds have 
 * passed so that the first task can display a message. Test your classes using an Executor.
 */

#include <iostream>
#include <string>
#include <boost/thread/thread.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread/locks.hpp>
#include <boost/thread/condition_variable.hpp>
using namespace std;
using namespace boost::posix_time;

class Runnable1 {
private:
	boost::thread* t;
	boost::mutex mtx;
	boost::condition_variable cond;
	
	typedef boost::unique_lock<boost::mutex> Lock;

	Runnable1(const Runnable1&);
	Runnable1& operator = (const Runnable1&);

public:
	Runnable1() {
		t = new boost::thread(boost::ref(*this));
	}

	~Runnable1() {
		if(t) {
			if(t->joinable())
				t->join();
			delete t;
		}
	}

	void displayMessage() {
		Lock lock(mtx);
		cond.wait(lock);
		cout << "Wait Over... Message: What do I do now??" << endl;
	}

	void operator() () {
		try {
			displayMessage();
		} catch(const boost::thread_interrupted&) { 
			cout << "Runnable1 interrupted" << endl;
		}
	}

	boost::condition_variable& getCondition() {
		return cond;
	}
};


class Runnable2 {
private:
	boost::thread* t;
	Runnable1& run1;

	Runnable2(const Runnable2&);
	Runnable2& operator = (const Runnable2&);

	typedef boost::unique_lock<boost::mutex> Lock;

public:
	Runnable2(Runnable1& run1Arg) : run1(run1Arg) {
		t = new boost::thread(boost::ref(*this));
	}

	~Runnable2() {
		if(t) {
			if(t->joinable())
				t->join();
			delete t;
		}
	}

	void operator() () {
		cout << "Sleeping for 5 seconds" << endl;
		boost::this_thread::sleep(seconds(5));
		cout << "Notifying everyone" << endl;
		run1.getCondition().notify_all();
	}
};

int main() {
		Runnable1 run1;
		Runnable2 run2(run1);

		boost::this_thread::sleep(seconds(10));

		return 0;
}
