/*
Simple program to demo boost::thread
*/

#include <iostream>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread/thread.hpp>
#include <string>
#include <sstream>
using namespace std;
using namespace boost::posix_time;

class LiftOff {
private:
	static int taskCount;
	unsigned int count ;
	const unsigned int id;

public:
	LiftOff() : id(taskCount++) , count (10) {
	}

	string status() {
		ostringstream oss;
		if(count > 0) {
			oss << "#"; oss << id; oss << "("; oss << count; oss << "), ";
		}
		else {
			oss << "LiftOff..!!";
		}
		return oss.str();
	}

	void operator () () {
		while(count-- > 0) {
			cout << status();
			boost::this_thread::yield();
		}
	}
};

int LiftOff::taskCount =  0;

int main() {
	LiftOff lo;

	boost::thread t1(lo);

	t1.join();
	cout << endl << "Done" << endl;

	return 0;
}	
