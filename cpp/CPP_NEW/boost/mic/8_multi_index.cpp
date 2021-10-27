#include <iostream>
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/identity.hpp>
#include <boost/shared_ptr.hpp>
#include <utility>

using namespace std;
using namespace boost;
using namespace boost::multi_index;

struct A {
public:
    const int id;

public:
    explicit A(const int& pId) : id(pId)
    {};

    friend bool operator < (const A& lhs, const A& rhs) {
        return lhs.id < rhs.id;
    }

    friend ostream& operator << (ostream& os, const A& rhs) {
         os << "A with id: "<< rhs.id;
         return os;
    }
};

typedef boost::shared_ptr<A> ITEM;

#if 1
typedef boost::multi_index_container< ITEM,
               indexed_by < 
                   ordered_unique <BOOST_MULTI_INDEX_MEMBER (A, const int, id) >
               >
         > ATable;
#endif

//typedef boost::multi_index_container< ITEM > ATable;

int main()
{
    ATable at;
    boost::shared_ptr<A> aPtr(new A(100));

    typedef ATable::nth_index<0>::type::iterator Iterator;

    cout << "ATable size before : " << at.size() << endl;

    std::pair<Iterator, bool> returnValue = at.insert(aPtr);
    if(returnValue.second == true) {
        cout << "Inserted: " << **returnValue.first << endl;
    }
    else {
        cout << "Not Inserted because of conflicting item: " << **returnValue.first << endl;
    }

    cout << "ATable size After: " << at.size() << endl;

    cout << "Trying find now." << endl;
    aPtr.reset(new A(100));
    //Iterator iter = at.find(aPtr);
    Iterator iter = at.find(100);
    if(iter != at.end()) {
        cout << "Found" << endl;
    }
    else {
        cout << "Not Found" << endl;
    }

    return 0;
}
   
