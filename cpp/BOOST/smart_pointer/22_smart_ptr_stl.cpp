/*
An important question is how to use smart ptr's with STL Algorithms which actually does not work on the pointers but the actual value pointed by them.
The answer is to use predicates as shown below
*/

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>

using namespace std;
using boost::weak_ptr;
using boost::shared_ptr;

template <typename Func, typename T>
struct weak_ptr_unary_t : public std::unary_function<weak_ptr<T>, bool> {
private:
	T _t;
	Func _f;
public:
	weak_ptr_unary_t(const Func& f, const T& t) : _t(t), _f(f)
	{ }

	bool operator() (weak_ptr<T> wp) const {
		boost::shared_ptr<T> sp = wp.lock();
		if(sp) {
			return _f(*sp, _t);
		}
		else {
			return false;
		}
	}
};

template <typename Func, typename T>
weak_ptr_unary_t<Func, T> weak_ptr_unary(const Func& f, const T& t) {
	return weak_ptr_unary_t<Func, T>(f, t);
}

int main() {

	vector<weak_ptr<string> > vec;

	shared_ptr<string> sp1(new string("An example "));
	shared_ptr<string> sp2(new string("of using "));
	shared_ptr<string> sp3(new string("smart pointers and predicates."));
	
	vec.push_back(weak_ptr<string>(sp1));
	vec.push_back(weak_ptr<string>(sp2));
	vec.push_back(weak_ptr<string>(sp3));

	vector<weak_ptr<string> >::iterator it = find_if(vec.begin(), vec.end(), weak_ptr_unary(std::equal_to<string>(), string("of using ")));

	if(it != vec.end()) {
		shared_ptr<string> sp(*++it);
		cout << *sp << endl;
	}
	return 0;
}
