#include <iostream>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <stdexcept>
#include <string>
using namespace std;
using namespace boost::gregorian;

int main() {
	//1. Simplest way to create a date. Enter the year, month and date.
	//An out_of_range() exception is thrown if any parameter is invalid.
	try {
		cout << "Constructing date using date(year, month, date) format" << endl;
		date d(2011, Feb, 10);
		cout << d << endl;

		//date d2(2011, Feb, 29);
		//date d3(1000, Jan, 01);
		//date d4(1500, Oct, 32);
	} catch(std::out_of_range& e) {
		cout << "Invalid date: " << e.what() << endl;
	}

	//2. Use Copy c'tor
	date d (2012, Jan, 28);
	date d2(d);
	cout << "\nConstructing date using copy c'tor" << endl;
	cout << d2 << endl;

	//3.Constructing date using a special value, like: neg_infin, pos_infin, not_a_date_time, max_date_time, min_date_time.
	cout << "\nNot a date time" << endl;
	date d3(not_a_date_time);
	cout << d3 << endl;

	//4. Default constructor. Can be disabled by using the "-D  DATE_TIME_NO_DEFAULT_CONSTRUCTOR" compile time flag.
	date d5;
	cout << "\nDate using default constructor" << endl;
	cout << d5 << endl;

	//5. From std::string, Order is yyyy/mm/dd.
	std::string str("2002/1/25");
	date d6(from_string(str));
	cout << "\nDate from string" << endl;
	cout << d6 << endl;

	//6. From std::string, but not delimited, order: yyyymmdd 
	std::string str2("20020125");
	date d7(from_undelimited_string(str2));
	cout << "\nDate from undelimited string" << endl;
	cout << d7 << endl;

	//7. You can also get the UTC day and the local day as follows.
	//This would make sence if you change you clock time to 1:00AM in the morning and then run the program.
	date d8(day_clock::local_day());
	cout << "\nLocal Day: " << d8 << endl;
	date d9(day_clock::universal_day());
	cout << "\nUniversal (UTC) Day: " << d9 << endl;

	//Accessors
	date d10(2020, Jan, 25);
	cout << "\nAccessors:" << endl;
	cout << "Year: " << d10.year() << endl;
	cout << "Month: " << d10.month() << endl;
	cout << "Day: " << d10.day() << endl;
	cout << "Day Of Week: " << d10.day_of_week() << endl;
	cout << "Day Of Year: " << d10.day_of_year() << endl;
	
	//Get the date (year, month and day) as a struct called date::ymd_type and use ymd.year, ymd.month and ymd.day variables.
	date::ymd_type ymd = d10.year_month_day();
	cout << "ymd_type Day: " << ymd.day << endl;
	cout << "ymd_type Month: " << ymd.month << endl;
	cout << "ymd_type Year: " << ymd.year << endl;
	
	cout << "\nEnd Of Month Date: " << d10.end_of_month() << endl;

	//Conversions to string
	cout << "\nDate to Strings:" << endl;
	cout << "To Simple String: " << to_simple_string(d10) << endl;
	cout << "To ISO String: " << to_iso_string(d10) << endl;
	cout << "To ISO Extended String: " << to_iso_extended_string(d10) << endl;

	//You can also convert date to the C++ standard date structure tm. Its trivial if you look online.

	return 0;
}

