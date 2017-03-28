/*
 * You can also create a boost::thread as a daemon. For this you should join your thread and run your application in the background.
 */

#include <iostream>             
#include <string>       
#include <boost/thread/thread.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/shared_ptr.hpp> 
                        
using namespace boost::posix_time;
using namespace std;

/*
 * Create a simple function which writes to the console for sometime and then exits.
 */
void countDown(int counter) {
	do {
		cout << "[" << counter << "]" << endl;
		boost::this_thread::sleep(seconds(1));
	}while(counter-- > 0);
}

int main() {
	boost::thread t(&countDown, 10);

	cout << "Main thread sleeping for a while" << endl;
	boost::this_thread::sleep(seconds(2));
	cout << "Exiting main" << endl;

	t.join();
	
	return 0;
}

