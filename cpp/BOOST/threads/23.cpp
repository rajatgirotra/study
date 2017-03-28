/*
 * Program to show how thread.join() always waits; even in the face of exceptions. Also you'll see how to handle thread_interrupted exception.
 */

#include <iostream>
#include <string>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread/thread.hpp>
using namespace std;
using namespace boost::posix_time;

class Sleeper {
private:
	int durantionInSecs;
	string name;

public:
	Sleeper(const string& pName, const int& arg = 5) : name(pName), durantionInSecs(arg) {
	}

	void operator() () {
		try {
			boost::this_thread::sleep(seconds(durantionInSecs));
		}catch(const boost::thread_interrupted& e) {
			cout << "Thread " << name << " interrupted" << endl;
			return;
		}
		cout << "Thread " << name << " has awakened" << endl;
	}
};

class Joiner {
private:
	boost::thread& t;
	string name;

public:
	Joiner(const string& pName, boost::thread& tArg) : name(pName), t(tArg) {
	}

	void operator() () {
		try {
			t.join();
		}catch(const boost::thread_interrupted& e) {
			cout << "Thread " << name << " interrupted" << endl;
		}
		cout << "Thread " << name << " join completed" << endl;
	}
};

int main() {
	Sleeper sleepy("Sleepy", 3),
	        grumpy("Grumpy", 3);

	boost::thread t1(sleepy);
	boost::thread t2(grumpy);

	Joiner dopey("Dopey", t1),
		doc("Doc", t2);

	boost::thread t3(dopey);
	boost::thread t4(doc);

	t2.interrupt();

	t1.join();
	t2.join();
	t3.join();
	t4.join();
	
	return 0;
}
