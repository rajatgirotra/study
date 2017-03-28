/* date_periods */

#include <iostream>
#include <boost/date_time/gregorian/gregorian.hpp>
using namespace std;
using namespace boost::gregorian;

int main() {
	//Period is between [begin, end), ie, here it is just one day.
	date_period dp(date(2020,Jan, 10), date(2020, Jan, 22));

	//Methods on Date Periods.
	cout << "First Day of period: " << dp.begin() << endl;
	cout << "Last Day of period: " << dp.last() << endl; //returns (end - 1)  date
	cout << "End day of period: " << dp.end() << endl;
	cout << "Is Date Period null: " << dp.is_null() << endl;
	cout << "Date Period length: " << dp.length() << endl;

	cout << endl << endl;

	date_period dp2(date(2012, 12, 31), days(5));
	cout << "First Day of period: " << dp2.begin() << endl;
	cout << "Last Day of period: " << dp2.last() << endl; //returns (end - 1)  date
	cout << "End day of period: " << dp2.end() << endl;
	cout << "Is Date Period null: " << dp2.is_null() << endl;
	cout << "Date Period length: " << dp2.length() << endl;

	//There are a lot of other functions like
	//contains(), intersects(), intersection(), is_adjacent(), is_after(), is_before() etc... 
	//Have a look online.
	
	return 0;
}

		

