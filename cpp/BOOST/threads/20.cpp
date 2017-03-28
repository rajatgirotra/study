/*
 * Program to show how to use the unique_future and packaged_task classes.
 */

#include <iostream>
#include <string>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread/thread.hpp>
#include <boost/thread/future.hpp>
#include <sstream>
#include <vector>
using namespace boost::posix_time;
using namespace std;

class CallableDemo {
private:
	int id;

public:
	CallableDemo(int arg) : id(arg) {}

	string operator() () {
		boost::this_thread::sleep(seconds(5));

		cout << "Id: " << id << endl;
		ostringstream oss;
		oss << "CallableDemo object " << id << endl;
		return oss.str();	
	}
};

int main() {
	vector<boost::shared_future<string> > resultsVec;
	boost::packaged_task<string>* pt[10];
	boost::thread* t[10];

	int i = 0;
	for(i = 0; i < 10; ++i) {
		pt[i] = new boost::packaged_task<string> (CallableDemo(i));
	}

	for(i = 0; i < 10; ++i) {
		boost::shared_future<string> sf = pt[i]->get_future();
		resultsVec.push_back(sf);
	}

	for(i = 0; i < 10; ++i) {
		t[i] = new boost::thread(boost::ref(*(pt[i])));
	}

	for(i = 0; i < 10; ++i) {
		boost::shared_future<string> sf = resultsVec[i];
		cout << boolalpha << sf.has_value() << endl;
		cout << sf.get() << endl;
	}

	for (i = 0; i < 10; ++i) {
		t[i]->join();
	}

	for (i = 0; i < 10; ++i) {
		delete t[i];
		delete pt[i];
	}

	//resultsVec.clear();

	return 0;
}
