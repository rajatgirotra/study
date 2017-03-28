/*
Some simple free functions on shared_ptr

1]

template<class T, class U>
bool operator==(shared_ptr<T> const & a, shared_ptr<U> const & b); // never throws


Returns: a.get() == b.get(), i.e. equality holds if both shared_ptrs are sharing ownership, or are both empty.



2] 
template<class T, class U>
bool operator!=(shared_ptr<T> const & a, shared_ptr<U> const & b); // never throws


Returns: a.get() != b.get().

Opposite of above.


3] 

template<class T, class U>
bool operator<(shared_ptr<T> const & a, shared_ptr<U> const & b); // never throws

returns: *a.get() < *b.get()

*/

#include <iostream>
#include <boost/shared_ptr.hpp>
#include <set>
#include <string>
using namespace std;


class Person {
private:
	string lastname;
	string firstname;

public:
	Person(const string& fn, const string& ln) : firstname(fn), lastname(ln) { }

	bool operator < (const Person&) const;

	friend ostream& operator << (ostream& os, const Person*);
	friend ostream& operator << (ostream& os, const Person&);
};

bool Person::operator < (const Person& rhs) const {

	if(lastname < rhs.lastname) 
		return true;
	else if (lastname > rhs.lastname)
		return false;
	else
		return firstname < rhs.firstname;
} 

ostream& operator << (ostream& os, const Person* lhs) {
		os <<  "FirstName: " << lhs->firstname << "    LastName: " << lhs->lastname << endl;
		return os;
}

ostream& operator << (ostream& os, const Person& lhs) {
		os <<  "FirstName: " << lhs.firstname << "    LastName: " << lhs.lastname << endl;
		return os;
}


struct Compare {
bool operator () (const boost::shared_ptr<Person>& lhs, const boost::shared_ptr<Person>& rhs) const {
	return *lhs < *rhs;
}
};

int main() {
	boost::shared_ptr<int> a, b;
	cout << std::boolalpha << (a == b) << endl; //true as both ptrs are empty.

	a = boost::shared_ptr<int>(new int (9));
	cout << std::boolalpha << (a == b) << endl; //false as b is empty and a is non empty.
	cout << a.use_count() << endl; //should be 1.

	b = boost::shared_ptr<int>(new int (9));
	cout << std::boolalpha << (a == b) << endl; //false as both a and b refer to different pointers.

	a.reset(); b.reset();
	int* ptr = new int(78);
	
	a = boost::shared_ptr<int>(ptr);
	b = a;
	cout << (a == b) << endl; //true as both a and b refer to same pointers.

	set<boost::shared_ptr<Person> , Compare> personSet;
	//set<boost::shared_ptr<Person> > personSet;

	//boost::shared_ptr<Person> p(new Person("Rajat", "Girotra"));
	//personSet.insert(p);
	personSet.insert(boost::shared_ptr<Person> (new Person("Rajat", "Girotra")));
	personSet.insert(boost::shared_ptr<Person> (new Person("Jitin", "Sethi")));
	personSet.insert(boost::shared_ptr<Person> (new Person("Shweta", "Sethi")));
	personSet.insert(boost::shared_ptr<Person> (new Person("Vidhu", "Girotra")));
	personSet.insert(boost::shared_ptr<Person> (new Person("Puneet", "Monga")));

	set<boost::shared_ptr<Person> >::iterator iter = personSet.begin();

	while(iter != personSet.end()) {
		//cout << *iter << "   Use Count = " << (*iter).use_count() << endl; //Both this and the below work.
		// ostream operator for shared_ptr is overloaded. it calls os << p.get(), so we have overloaded operator << in Person accordingly.
		
		cout << **iter << "   Use Count = " << (*iter).use_count() << endl; 
		
		iter++;
	}
	return 0;
}

/*
The only big question is that the default comparison function for set does not seem to work.
*/
