#include <iostream>
#include <string>
#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <boost/ref.hpp>

using namespace std;

class MyClass {
public:
	string foo(int x, int y) {
		cout << "X: " << x << "     Y: " << y << endl;
		return "Hello World";
	}
};

class Task {
public:
	typedef boost::function0<void> Functor1;

	typedef boost::function4<string, MyClass*, int, int, double> Functor2;

	void execute() {
	  func1();
	  //func2(new MyClass(), 10, 20, 78.9);
	}

	
	Task(Functor1 pFunc) : func1(pFunc) {
	}

   /*
    Task(Functor2 pFunc) : func2(pFunc) {
	} */


private:
	Functor1 func1;
	Functor2 func2;

};


int main() {
	MyClass c;
	Task task(boost::bind<string>(&MyClass::foo, boost::ref(c), 4, 67));

	task.execute();
	return 0;
}

// The above shows that you what boost::bind returns can be bound to any boost::function
// This is somehwat complex and you must study the two JPEG's i have pasted alongside 
// to completely understand what how boost bind and boost function work.
//
//
// Another way to think about it in a simplistic way is:
//
// boo::bind() will return you a nullary function object(), i.e. a function object which is complete in itself and does
// not need any more arguments. So such a function object can be assigned to 
//
// boost::function0<void> FUNC;
// boost::function3<string, int, double, const char*> FUNC;
// or any other bull shit boost::functionN<> type.
//
// If you create a boost::bind() which takes parameters (i.e placeholders like _1, _2 etc in boost::bind()), then
// boost::function must have the knowledge of the types of these parameters and must declare itself accordingly.
//
// You'll see in Task.hpp that we declare a boost::function0<void> FUNC, because the task class needs no information
// about the function which it will run in a thread. It is just a thread in which you can run any function.
//
// However, in deposit_stp_handler, you have StpMessageSender.hpp in which you declare
// typedef boost::function< void (StpMessageSenderEvent evt,const idl::fx::deposit::DepositTransaction &) >  Handler;
//
// and then initialise it later using boost::bind(&DealhubEventHandler::process, dhEvtHdlr_, _1, _2) and then call it
// like below:
// _handler(SENT,*(iter->_depTrans));
//
// So yo need to decide whether the function you are binding will have arguments (_1, _2 etc). and then decide who and
// how will these arguments be populated later.

