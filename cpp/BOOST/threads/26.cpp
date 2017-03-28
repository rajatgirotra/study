/*
 * This program shows how to use thread_specific_ptr.
 */

#include <iostream>
#include <string>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread/thread.hpp>
#include <boost/thread/tss.hpp>
#include <cassert>
using namespace std;
using namespace boost::posix_time;

/*
 * Since each thread will have its own copy of thread_specific_ptr, and since we are wrapping that pointer inside another class,
 * ThreadLocalVariableHolder (in this case), we should make sure that we have separate copies of this object for different threads,
 * else we are likely to get into serious issues
 */

class ThreadLocalVariableHolder {
private:
	boost::thread_specific_ptr<int> tsp;

public:
	ThreadLocalVariableHolder(int* pArg) {
		assert(pArg != 0);
		tsp.reset(pArg);
	}

	void increment() {
		int* val = tsp.get();
		assert(val != 0);
		++(*val);
	}

	int get() const {
		return *tsp;
	}

	~ThreadLocalVariableHolder() {
		cout << "Deleting ThreadLocalVariableHolder() with value:  " << get() << endl;
	}
};
	

class Accessor {
private:
	boost::thread* t;
	int id;

	int* thread_specific_value;
	//responsibility of deleting this is with the thread_specific_ptr object.

public:
	Accessor(int pId, int* initValue) : id(pId), thread_specific_value(initValue) {
		t = new boost::thread(boost::ref(*this));
	}

	~Accessor() {
		if(t) {
			if(t->joinable())
				t->join();
			delete t;
		}
	}

	void operator() () {
		//First set the thread_specific_ptr.
		ThreadLocalVariableHolder tss(thread_specific_value); //separate copy of this object for this thread.
		while(!boost::this_thread::interruption_requested()) {
			tss.increment();
			cout << this->toString(tss) << endl;
			boost::this_thread::yield();
		}
	}

	string toString(const ThreadLocalVariableHolder& tss) {
		ostringstream oss;
		oss << "#id: " << id <<  "  Local Variable: " << tss.get();
		return oss.str();
	}

	void interrupt() {
		this->t->interrupt();
	}
};

int main() {
	int* a = new int(56);
	int* b = new int(-78);

	Accessor aAcc(1, a);
	Accessor bAcc(2, b);
	
	boost::this_thread::sleep(seconds(2));

	aAcc.interrupt();
	bAcc.interrupt();

	return 0;
}
	
