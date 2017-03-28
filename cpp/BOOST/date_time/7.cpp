#include <iostream>
#include <boost/date_time/gregorian/gregorian.hpp>
using namespace std;
using namespace boost::gregorian;

int main() {
	//Get your birth date.
	//Then get the local day.
	//Calculate the no. of days you've lived so far.

	string str;
	cout << "Enter your date of birth: (yyyy-mm-dd): " << endl;
	cin >> str;
	
	date dob(from_string(str));

	date today(day_clock::local_day());

	days days_alive = today - dob;

	cout << "You've been alive for " << days_alive << " days."<< endl;

	return 0;
}

