/*
 * We create an Ornamental Garden here. The garden has four gates. and people can enter from any gate. We have to keep track of the number of people entering from each gate
 * and the total number of people in the garden also. So we create 4 threads for monitoring the number of people entering from each gate. and also keep a global count
 * of the total number of people.
 */

#include <iostream>
#include <string>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread/thread.hpp>
#include <boost/thread/locks.hpp>
#include <cstdlib>
#include <list>
using namespace std;
using namespace boost::posix_time;

class Count { //class to keep track of the total no. people in the garden.

private:
	long number;
	boost::mutex mtx;


public:

	Count() : number(0) { 
		srand(47);
	}

	long increment() {
		boost::lock_guard<boost::mutex> lg(mtx);
		long temp = number;
		if(rand() % 2 == 0) {
			boost::this_thread::yield();
		}
		return (temp == ++number);
	}

	long value() {
		boost::lock_guard<boost::mutex> lg(mtx);
		return number;
	}
};

class Entrance {
private:
	//private Copy c'tor and assignment
	Entrance(const Entrance&);
	Entrance& operator = (const Entrance&);

	//Each entrance will have an id and a count of the number of people entering through that Entrance
	int id;
	long number;

	//Each Entrance object is a self managing thread.
	boost::thread* t;

	//Static variable Count that will be shared by all Entrance threads.
	static Count count;
	static volatile bool cancel; //used to signal that gates are now closed.

	static list<Entrance*> _entranceList;

public:

	//C'tor
	Entrance(const int& pId) : id(pId), number(0) {
		_entranceList.push_back(this);
		t = new boost::thread(boost::ref(*this));
	}

	//D'tor
	~Entrance() {
		if(t) {
			if(t->joinable()) {
				t->join();
			}
			delete t;
		}
	}


	//function to close all gates
	static void close() {
		cancel = true; //gates are now closed
	}

	void operator() () {
		while(cancel == false) {
			++number;
			cout << "Entrance " << id << " Number: " << number << " Total: " << count.increment() << endl;
		}
	}

	static long getTotalCount() {
		return count.value();
	}

	static long sumEntrances() {
		long sum = 0;
		for(list<Entrance*>::iterator iter = _entranceList.begin(); iter != _entranceList.end(); ++iter) {
			 sum += (*iter)->number;
		}
		return sum;
	}
};

Count Entrance::count;
volatile bool Entrance::cancel = false;
list<Entrance*> Entrance::_entranceList;


int main() {
	Entrance* entArray[5];

	int i = 0;
	for(i = 0; i < 5; ++i) {
		entArray[i] = new Entrance(i);
	}

	//wait for 5 seconds;
	boost::this_thread::sleep(seconds(5));

	//Close the gates.
	Entrance::close();

	//Await termination
	boost::this_thread::sleep(seconds(2));

	cout << "Total Count: " << Entrance::getTotalCount() << endl;
	cout << "Sum Entrance: " << Entrance::sumEntrances() << endl;

	for(i = 0; i < 5; ++i) {
		delete entArray[i];
	}

	return 0;
}
	
