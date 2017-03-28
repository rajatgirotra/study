#include <iostream>
#include <set>
using namespace std;

class A
{
private:
	int a;
	static int tag;

public:
	A() {
		cout << "A c'tor" << endl;
		a = ++tag;
	}

	A(const A& rhs) {
		cout << "A copy c'tor"<< endl;
                a = rhs.a;
	}

	~A() {
		cout << "A d'tor" << endl;
	}

	void display() const {
		cout << "A with tag: " << a << endl;
	}

	friend bool operator < (const A& lhs, const A& rhs) {
		return lhs.a < rhs.a ;
	}
};

int A::tag = 0;

int main() {
	set<A> s;

	s.emplace(A());

        cout << "OK" << endl;
	set<A>::iterator it = s.begin();
	while (it != s.end() ) {
		it->display();
		++it;
	}

	cout << s.size() << endl;
	s.erase(s.begin());
	cout << s.size() << endl;
}
