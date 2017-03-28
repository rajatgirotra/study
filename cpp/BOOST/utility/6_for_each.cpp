/*
Boost For each is just a simple macro which is designed for ease of use. There is nothing fancy about it. Very simple and straight-forward.
Just include boost/foreach.hpp
*/

#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <boost/foreach.hpp>
#include <iomanip>

using namespace std;

int main() {
	std::string str("Hello World");

	//Boost.foreach
	BOOST_FOREACH(char ch, str) {
		cout << ch << endl;
	}
	//So you are basically iterating over a sequence. But the question is
	//what constitutes a sequence??

	/*One thing is that BOOST_FOREACH is built on top of Boost.Range, so it automatically supports
      all those types which Boost.Range recognizes as a sequence. Eg:
	  1] STL container
	  2] std::string
	  3] arrays
	  4] std::pair of iterator (I really dont know what this is at this moment, but I'll find out)
	  */
	/*
	If you want to use BOOST_FOREACH with your own user defined class, all you have to do is
	1] Create a nested iterator and const_iterator
	2] Provide begin() and end() functions.
	*/

	/*Iterate over an stl container*/
	list<int> intList;
	intList.push_back(10);
	intList.push_back(20);
	intList.push_back(30);
	intList.push_back(40);
	intList.push_back(50);

	int i = 0;
	BOOST_FOREACH (i, intList) {
		cout << i << " ";
	}
	cout << endl;

	/* BOOST_REVERSE_FOREACH is also available */
	BOOST_REVERSE_FOREACH (i, intList) {
		cout << i << " ";
	}
	cout << endl;

	/* Iterate now over an array */
	short shArray[] = { -9, -8, -7, -6, -5 };

	BOOST_FOREACH(i , shArray) {
		cout << i << "   "; //Here short is implicitly promoted to integer. You can use a short also anyway.
	}
	cout <<endl;


	/* Iterating over a nested sequence */
	vector<vector <string> > familyNames;
	vector<string> husbandNames;
	vector<string> wifeNames;

	husbandNames.push_back("Rajat");
	husbandNames.push_back("Jitin");
	husbandNames.push_back("Jack");
	husbandNames.push_back("Mark");
	wifeNames.push_back("Vidhu");
	wifeNames.push_back("Shweta");
	wifeNames.push_back("Jackoline");
	wifeNames.push_back("MarksWife");

	familyNames.push_back(husbandNames);
	familyNames.push_back(wifeNames);

	BOOST_FOREACH(vector<string> names, familyNames) {
		cout << endl;
		BOOST_FOREACH(string str, names)
			cout << setw(12) << str;
	}
	return 0;
}

/*
Many developers typedef BOOST_FOREACH further for ease of use

typedef foreach_ BOOST_FOREACH
*/