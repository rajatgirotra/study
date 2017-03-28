#include <iostream>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <stdexcept>
#include <string>
using namespace std;
using namespace boost::gregorian;

int main() {
	days dd(2);
	cout << dd.days() << endl;

	days dd2(not_a_date_time);
	cout << dd2.days() << endl; //Prints garbage.
	cout << dd2.is_special() << endl;

	days dd3(3);
	days dd4(4);
	days dd5 = dd3 + dd4;
	cout << dd5 << endl;

	dd5 -= dd5; //reduce dd5 to zero.
	cout << dd5 << endl;

	days dd6(-9);
	cout << dd6 << endl;


	return 0;
}

