/*
 * Self managed thread. A class which runs its overloaded function call operator() method automatically in a new thread when the class object is created. 
 */

#include <iostream>
#include <string>
#include <boost/thread/thread.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/shared_ptr.hpp>

using namespace boost::posix_time;
using namespace std;
class Callable {
	private:
		boost::thread* t;

		//Make copy c'tor and assignment operator private
		Callable(const Callable&);
		Callable& operator = (const Callable&);

	public:
		Callable() {
			//Note that we are passing *this as ref. If you pass it by value,
			//it will be a classical bug, which took me a lot of time to debug.
			//In pass by value, another Callable object is created which
			//also shared the thread t. So two Callable objects sharing the same 
			//pointer. which results in core dump when the objects are destroyed.
			//The best way is to disable copy c'tor for self managed thread classes.
			t = new boost::thread(boost::ref(*this));
		}

		~Callable() {
			if(t) {
				if(t->joinable())
					t->join();
				delete t;
			}
		}

		void operator() () {
			boost::this_thread::sleep(seconds(6));
			cout <<"Managed thread sleep over: thread id: " << boost::this_thread::get_id() << endl;
		}

};

int main() {
	//Callable c[5];
	Callable c;
	boost::this_thread::sleep(seconds(1));
	cout <<"Main thread sleep over" << endl;
	return 0;
}

