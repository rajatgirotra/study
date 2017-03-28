/*
Future - This is another concept which allows you to return values from a thread and also to wait synchronously until the thread finishes executing. There are 4 classes here:
Two classes are used to wait for asynchronous results:

1] boost::unique_future<T> - This class holds only one reference to the result. If you copy this object, you transfer ownership of the result. Just like auto_ptr.
2] boost::shared_future<T> - Here you can have multiple objects holding a reference to the result. 
You can also convert a unique_future into a shared_future object but not vice-versa.

The other two classes are used to generate the results.

1] boost::promise<T>
2] boost::packaged_task<T> - This basically encapsulates a function object or a function pointer and runs that object or function in a separate task.
*/

#include <iostream>
#include <string>
#include <boost/thread/thread.hpp>
#include <boost/thread/future.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
using namespace std;
using namespace boost::posix_time;

string sayHello() {
	//Sleep for 10 second before reurning result
	boost::this_thread::sleep(seconds(10));
	return "Hello World";
}


int main() {
	boost::packaged_task<string> pt(&sayHello); // encapsulate a function pointer
	
	boost::unique_future<string> uf; //an empty unique future.

	//Some API of unique_future.
	
	//1. Get the state.
 	boost::future_state::state st = uf.get_state(); //uninitialised, waiting or ready.
	cout << "State: " << st << endl; //should be 0, which is uninitialised
	cout << "isReady: "<< boolalpha << uf.is_ready() << endl;	//should be false
	cout << "hasException: "<< boolalpha << uf.has_exception() << endl;
	cout << "hasValue: "<< boolalpha << uf.has_value() << endl;
	try {
		cout << "get: "<< uf.get() << endl; //throws boost::future_uninitialised exception.
	} catch(boost::future_uninitialized& fu) {
		cout << "Exception caught: " << fu.what() << endl;
	}

	//Associate a result with this unique_future.
	uf = pt.get_future();
	
	cout << endl;
	cout << "After initialization" << endl;
	//1. Get the state.
 	st = uf.get_state(); //uninitialised, waiting or ready.
	cout << "State: " << st << endl; //should be 1, which is waiting
	cout << "isReady: "<< boolalpha << uf.is_ready() << endl;	//should be false
	cout << "hasException: "<< boolalpha << uf.has_exception() << endl;
	cout << "hasValue: "<< boolalpha << uf.has_value() << endl;

	//The call to get blocks until the task has completed.
	//So first trigger the task and then call unique_future.get()

	boost::thread t1(boost::move(pt)); //I think we use boost::move() because pt is not copyable, but will need to confirm it though.

	//Call wait which will block until results are available.
	uf.wait(); //here calling wait is not very useful, as the call to get blocks anyway.
			//We show it here just to tell you that the API is available, and also the API timed_wait();

	cout << "After Wait over" << endl;
	try {
		cout << "get: "<< uf.get() << endl; //throws boost::future_uninitialised exception.
	} catch(boost::future_uninitialized& fu) {
		cout << "Exception caught: " << fu.what() << endl;
	}


	cout << endl;
	cout << "After getting results back." << endl;
	//1. Get the state.
 	st = uf.get_state(); //uninitialised, waiting or ready.
	cout << "State: " << st << endl; //should be 2, which is ready.
	cout << "isReady: "<< boolalpha << uf.is_ready() << endl;	//should be true
	cout << "hasException: "<< boolalpha << uf.has_exception() << endl;
	cout << "hasValue: "<< boolalpha << uf.has_value() << endl;

	return 0;
}	



/*
If you have more than one threads all which return some value which the caller is interested in, then boost provides a convenient API for that.

wait_for_any(F1& f1, F2& f2...) //where each Fn is of type unique_future or shared_future and wait until one result is ready.
wait_for_all(F1& f1, F2& f2...) //where each Fn is of type unique_future or shared_future and wait until all results are ready.

*/
