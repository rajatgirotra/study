/*
Boost provides a very good way of running a function only once in a multithreaded environment without causing any race conditions or deadlocks.
For this you first have to create an variable of boost::once_flag type which must be initialized statically to BOOST_ONCE_INIT.

Then you need to call the boost::call_once function passing the address of the function you want to run and this flag.

template <typename Callable>
void call_once(once_flag& flag, Callable func);

For this include <boost/thread/once.hpp>

*/

#include <iostream>
#include <string>
#include <boost/thread/thread.hpp>
#include <boost/thread/once.hpp>

using namespace std;
using namespace boost;

boost::once_flag f = BOOST_ONCE_INIT;


void Init() {
	cout << "Initialising" << endl;
}

struct callable {
	void operator() () {
		boost::call_once(f, &Init);
	}
};

int main() {
	callable x;
	boost::thread t1(x);
	boost::thread t2(x);

	t1.join(); t2.join();
	return 0;
}

/*
You'll notice that Initialising is output only once, affirming that the Init() function is called only once.
*/
