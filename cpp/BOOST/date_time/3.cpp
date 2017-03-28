#include <iostream>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <sstream>
using namespace std;
using namespace boost::posix_time;

int main() {
	time_duration td;
	cin >> td;

	cout << "Time: " << td << endl;

	string time = "14:35:23.987";
	stringstream ss(time);
	ss >> td;
	cout << td << endl;
	
	return 0;
}
