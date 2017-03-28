#include <iostream>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <sstream>
using namespace std;
using namespace boost::posix_time;

int main() {

	
	time_duration td (duration_from_string("22:10:00.000"));
	cout << td << endl;
}
