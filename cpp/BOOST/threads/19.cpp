/*
Same as 18.cpp but will multiple threads. Note that you need to call wait on all threads.
Also see how you can do that using the move assignment operator.
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

	LiftOff loArr[5];
	//boost::thread thArr[5] ;  //--->> A
	boost::thread* thArr[5] ;

	for(int i = 0; i < 5; ++i)
	   //thArr[i] = boost::detail::thread_move_t<boost::thread>(*(new boost::thread(loArr[i]))); //using the boost assignment operator.----> A
	   thArr[i] = new boost::thread(loArr[i]); //using the boost assignment operator.

	for(int i = 0; i < 5; ++i)
		//thArr[i].join(); //---> A
		thArr[i]->join();

	for(int i = 0; i < 5; ++i)
		delete thArr[i];

	return 0;
}	
