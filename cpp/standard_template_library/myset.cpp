#include <iostream>
#include <string>
#include <set>
using namespace std;

struct lesscmp {
	bool operator () (const int& lhs, const int& rhs) {
		return lhs < rhs;
	}
};

bool greatercmp (const int& lhs, const int& rhs) {
	return (lhs > rhs);
}

typedef bool (*funcPtr)(const int&, const int&);

int main() {

	set<int, lesscmp> lessSet;
	lessSet.insert(6);
	lessSet.insert(6);
	lessSet.insert(567);
	lessSet.insert(-889);
	lessSet.insert(0);

	set<int, lesscmp>::iterator it = lessSet.begin();
	while(it != lessSet.end())
		cout << *it++ << endl;

	set<int, funcPtr> greaterSet(greatercmp);
	greaterSet.insert(6);
	greaterSet.insert(6);
	greaterSet.insert(567);
	greaterSet.insert(-889);
	greaterSet.insert(0);

	cout << endl;
	set<int, funcPtr>::iterator iter = greaterSet.begin();
	while(iter != greaterSet.end())
		cout << *iter++ << endl;

	return 0;
} 

