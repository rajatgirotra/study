/*
 * Here we create a synchronization problem. We create a function which generates even integers. Then we create many threads which use this function and 
 * check if indeed the value is even. If not, an error is logged and the program terminates.
 *
 * See how using a boost::lock_guard() fixed the problem.
 */

#include <iostream>
#include <string>
#include <boost/thread/thread.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/thread/locks.hpp>
using namespace std;
using namespace boost::posix_time;

boost::mutex mtx;

class IntGenerator {
private:
	volatile bool bCanceled;

public:
	IntGenerator() : bCanceled(false) {
	}

	void cancel() {
		bCanceled = true;
	}

	bool isCanceled() const {
		return bCanceled;
	}

	virtual int next() = 0;
};

class EvenGenerator : public IntGenerator {
private:
	int val;

public:
	EvenGenerator() : val(0) {
	}

	int next() {
		//boost::lock_guard<boost::mutex> lg(mtx);
		//The good thing here is that even if an exception is raised, the lock will be unlocked
		//in lock_guard() d'tor. So you really dont need a try-finally {} clause in C++
		//as you have RAII.
		++val;
		//boost::this_thread::yield();
		++val;
		return val;
	}
};

class EvenChecker {
private:
	//This will be a self managed thread
	//private copy c'tor and assignment
	EvenChecker(const EvenChecker&);
	EvenChecker& operator = (const EvenChecker&);

	boost::thread* t;
	int id;
	IntGenerator& ig;

	static void test(IntGenerator& ig, int count) {
		int i = 0;
		boost::scoped_ptr<EvenChecker> consumerArray[count];
		for(i = 0; i < count; ++i) {
			consumerArray[i].reset(new EvenChecker(i, ig));	
		}
	}

public:
	EvenChecker(const int& pId, IntGenerator& pIg)  : id(pId), ig(pIg) {
		start();
	}

	void start() {
		t = new boost::thread(boost::ref(*this));
	}

	~EvenChecker() {
		if(t) {
			if (t->joinable())
				t->join();
			delete t;
		}
	}

	void operator() () {
		while(!ig.isCanceled()) {
			int val = ig.next();
			if(val % 2 == 0) {
				cout << "EvenChecker id: " << id << "      " << val << " is even" << endl;
			} else {
				cout << "EvenChecker id: " << id << "      " << val << " is NOT even" << endl;
				ig.cancel();
			}
		}
	}

	static void test() {
		IntGenerator* poIntGen = new EvenGenerator();
		test(*poIntGen, 10);
		delete poIntGen;
	}
};

int main() {
	EvenChecker::test();
	return 0;
}
