/*
 * Here we will test which operations cannot be interrupted by using thread.interrupt
 * We'll test the sleep operation, I/O operation, and synchronized blocking operations.
 */
#include <iostream>
#include <string>
#include <fstream>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread/thread.hpp>
#include <boost/thread/locks.hpp>

using namespace std;
using namespace boost::posix_time;

//Sleeping threads GET INTERRUPTED when thread.interrupt() is called
class SleepBlocked {

public:
	void operator() () {
		try {
			cout << "Sleeping for 10 seconds" << endl;
			boost::this_thread::sleep(seconds(10));
		} catch(const boost::thread_interrupted& e) {
			cout << "Exception caught during sleeping:"  << endl;
		}
	}
};

//I/O blocked threads DO NOT GET INTERRUPTED when thread.interrupt() is called
//The way out is to close the underlying object on which input is performed.
//This is not working as of now, so I'll return here later.
ifstream input;
class IOBlocked {
private:
	
public:
	void operator() () {
		try {
			int i;
			//input.open("abc.txt", ios_base::in);
			//input >> i; //block on an input operation
			cin >> i;
			cout << "Read: " << i << endl;
		}catch(boost::thread_interrupted& e) {	
			cout << "Exception caught during I/O operation:"  << endl;
		}
	}
};

boost::mutex mtx; //mutex to create a synchronized blocking call.
//Since boost::mutex is noncopyable, we can't move in inside the class.
//as the copy c'tor of the SynchronizeBlocked class will try to create a copy of this variable


//Calls waiting on mutex'es also DO NOT GET INTERRUPTED when thread.interrupt() is called
class SynchronizeBlocked {
	//Self managing thread class.
	boost::thread* t;

	SynchronizeBlocked& operator = (const SynchronizeBlocked&);
public:
	SynchronizeBlocked() {
		t = new boost::thread(boost::ref(*this));
	}

	SynchronizeBlocked(const SynchronizeBlocked& rhs) {
		t = 0;
	}

	void f() {
		boost::lock_guard<boost::mutex> lg(mtx);
		cout << "thread " << boost::this_thread::get_id() << " acquired lock on function f() "<< endl;
		while(!boost::this_thread::interruption_requested()) {
			boost::this_thread::yield(); //Never release the lock;
		}
	}

	~SynchronizeBlocked() {
		if(t) {
			t->detach();
			delete t;
		}
	}

	void operator() () {
		try {
			cout << "thread " << boost::this_thread::get_id() << " calling f() " << endl;
			f();
			cout << "Exiting thread " << boost::this_thread::get_id() << endl;
		}catch(boost::thread_interrupted& e) {
                        cout << "Exception caught during synchronized blocking operation:"  << endl;
                }
        }

	void interrupt() {
		t->interrupt();
	}
};


	

int main() {
	#if 0
	SleepBlocked sb;
	//Start the thread to sleep.
	boost::thread  t(sb);

	//Send an interrupt after 4 seconds
	boost::this_thread::sleep(millisec(400));
	cout << "Sending interrupt to sleeping thread after 4 seconds" << endl;
	boost::this_thread::sleep(seconds(4));
	t.interrupt();

	//Join until SleepBlocked is finished.
	t.join();
	#endif

	#if 0

	IOBlocked iob;
	//Start the thread to do I/O.
	boost::thread t2(iob);

	//Send an interrupt after 10 seconds
	boost::this_thread::sleep(seconds(10));
	cout << "Sending interrupt to I/O blocked thread after 10 seconds" << endl;
	t2.interrupt();

	//input.close();
	//Join until IOBlocked is finished.
	t2.join();
	#endif

	#if 1

        SynchronizeBlocked syncBlocked; //This will create a new thread and take the lock on function f();
        //Start the thread to call f() in another thread.
        boost::this_thread::sleep(millisec(300));
        boost::thread t3(syncBlocked);

        //Send an interrupt after 3 seconds
        boost::this_thread::sleep(seconds(3));
        cout << "Sending interrupt to SynchronizeBlocked thread" << endl;
        t3.interrupt();
	//Await termination (if it happens) 
        cout << "Awaiting termination for 10 seconds" << endl;
        boost::this_thread::sleep(seconds(10));
        cout << "thread " << t3.get_id() << " could not acquire lock on f()" << endl;
	syncBlocked.interrupt();
        boost::this_thread::sleep(seconds(2));
	#endif

	cout << "Ending main" << endl;
	//There is a problem here with SynchronizeBlocked class. When main ends, mtx is still in use and locked by a thread. This causes an assertion and core dump.
	//We need to figure out a way to avoid this.
	return 0;
}

