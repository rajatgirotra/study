#include <iostream>
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/identity.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/sequenced_index.hpp>
#include <boost/multi_index/mem_fun.hpp>
#include <boost/multi_index/global_fun.hpp>
#include <boost/multi_index/composite_key.hpp>
#include <string>
#include <algorithm>
#include <utility>

using namespace std;
using namespace boost;
using namespace boost::multi_index;

struct EmployeeDetails {
private:
public:
    unsigned int id; // Id of the employee.
    string given_name;
    string family_name;
    string home_phone_number;
    string cell_phone_number;

    //ctor
    EmployeeDetails(const unsigned int& pId,
                    const string& pGivenName,
                    const string& pFamilyName,
                    const string& pHomePhoneNumber,
                    const string& pCellPhoneNumber) : id(pId), given_name(pGivenName),
                                                  family_name(pFamilyName), home_phone_number(pHomePhoneNumber),
                                                  cell_phone_number(pCellPhoneNumber)
    { }

    friend ostream& operator << (ostream& os, const EmployeeDetails& rhs)
    {
       os << "Id: " << rhs.id << "  Name: " << rhs.given_name << " " << rhs.family_name
          << "  Home Phone: " << rhs.home_phone_number << "  Cell Phone: " << rhs.cell_phone_number;
       return os;
    }

    friend bool operator < (const EmployeeDetails& lhs, const EmployeeDetails& rhs)
    {
        return lhs.id < rhs.id;
    }

    const string& getCellPhoneNumber() const {
        return this->cell_phone_number;
    }
  
    static string fullName(const EmployeeDetails& rhs)
    { return rhs.given_name + rhs.family_name;  }
};

struct my_extractor {

    typedef string result_type;
    result_type operator() (const EmployeeDetails& ed) const noexcept {
        return ed.family_name;
    }
};

//MIC with ITEM = plain object and using most of the extractors.
typedef boost::multi_index_container < EmployeeDetails,
            indexed_by <
                //0th index based on employee id.
                ordered_unique < identity <EmployeeDetails> >, //Required operator < to be defined for EmployeeDetails
                //1st index, based on home phone number. 
                ordered_non_unique < BOOST_MULTI_INDEX_MEMBER(EmployeeDetails, std::string, home_phone_number) >,
                //2nd index, based on cell phone number 
                ordered_unique < BOOST_MULTI_INDEX_CONST_MEM_FUN(EmployeeDetails, const std::string&, getCellPhoneNumber) >,
                //3rd index, based on full Name
                ordered_non_unique < global_fun < const EmployeeDetails&, string , EmployeeDetails::fullName > >,
                //4th index, composite key, first family name in descending order, then given name in ascending order.
                ordered_non_unique < composite_key < EmployeeDetails,
                                                     BOOST_MULTI_INDEX_MEMBER(EmployeeDetails, string, family_name),
                                                     BOOST_MULTI_INDEX_MEMBER(EmployeeDetails, string, given_name)
                                     >,
                                     composite_key_compare<
                                         std::greater<string>,
                                         std::less<string>
                                     >
                >,
                //5th index, my own custom extractor.
                ordered_non_unique < my_extractor >
            >
        > EmployeeTable;


struct change_cell_phone_no {
       string newNo;
       change_cell_phone_no(const string& pNewNo) : newNo(pNewNo) {}

       void operator() (EmployeeDetails& ed) {
           ed.cell_phone_number = newNo;
       }
   }; 

struct changeBackTo_old_cell_phone_no {
       string newNo;
       changeBackTo_old_cell_phone_no(const string& pNewNo) : newNo(pNewNo) {}

       void operator() (EmployeeDetails& ed) {
           ed.cell_phone_number = newNo;
       }
   }; 


int main()
{

    EmployeeTable et;

    //The main functions that you can perform on a MIC are:
    //Copying,
    //insertion of an element,
    //hinted insertion, where a preexisting element is suggested in order to improve the efficiency of the operation,
    //deletion of an element,
    //Lookup (i.e find())
    //replacement of the value of an element, which may trigger the rearrangement of this element in one or more indices, or the banning of the replacement,
    //modification of an element, and its subsequent rearrangement/banning by the various indices.

    //We'll see later the difference between replacement and modification.

    //Insertion and Deletion
    //Insertion and erasing of elements are always performed through the appropriate interface of some index of the
    //multi_index_container; these operations, however, do have an impact on all other indices as well: for instance,
    //insertion through a given index may fail because there exists another index which bans the operation in order to
    //preserve its invariant (like uniqueness of elements.) 

    //Let us first add a few entries in the table.
    //To insert an item you first must get a reference to an index, then use that index to insert your item.
    //Insert returns you a std::pair, an iterator and a bool if the insertion was successful
    //Insertions may sometimes fail if any of the other indices fail to accept it.
    //If successful, iterator points to the element inserted, else it points to the element
    //which caused the insertion to fail.
    typedef EmployeeTable::nth_index<0>::type::iterator Iterator;
    std::pair<Iterator, bool> insertResult;

    insertResult = et.get<0>().insert(EmployeeDetails(1, "Rajat", "Girotra", "92716159", "82984850"));
    if(insertResult.second == true) {
        cout << "Inserting EmployeeDetails: " << *insertResult.first << " into MIC" << endl;
    }
    //insertResult = et.get<0>().insert(EmployeeDetails(1, "Rajat", "Girotra", "92716159", "82984850"));
    insertResult = et.get<0>().insert(EmployeeDetails(1, "Rajat", "Girotra", "92716159", "82984850"));
    if(insertResult.second == false) {
        cout << "Inserting EmployeeDetails failed/banned by existing element: " << *insertResult.first << endl;
    }

    //Just FYI: A way to create an iterator object for an index.
    boost::multi_index::nth_index<EmployeeTable, 0>::type::iterator ic0;

    et.get<1>().insert(EmployeeDetails(2, "Vidhu", "Ahuja", "92716159", "86066774"));
    et.get<2>().insert(EmployeeDetails(3, "Sudesh", "Ahuja", "25460995", "9871494404"));
    et.get<3>().insert(EmployeeDetails(4, "Vijay", "Ahuja", "25460995", "9818125914"));
    et.get<4>().insert(EmployeeDetails(5, "Shweta", "Sethi", "55555555", "9811207096"));
    et.get<5>().insert(EmployeeDetails(6, "Jitin", "Sethi", "55555555", "9811267202"));

    //Get access to any index type. That index will behave like a set or multiset in C++.
    //So the best way to print elements through an index is to use the iterator and copy algorithm.
    //Getting index 2, ie. cell phone no.
    const EmployeeTable::nth_index<2>::type& cell_index = et.get<2>();
    std::copy(cell_index.begin(), cell_index.end(), ostream_iterator<EmployeeDetails>(cout, "\n"));

    cout << endl;
    //Similarly, to erase you'll have to get a reference to an index
    //et.get<2>().erase("9871494404"); // Note the argument to erase is the type of the key only.
    //et.get<1>().erase("92716159"); // This erases more than one element.
    //std::copy(cell_index.begin(), cell_index.end(), ostream_iterator<EmployeeDetails>(cout, "\n"));

    //Actually erase() has 3 overloaded variants
    //iterator erase(iterator); returns the iterator pointing to the next element in the sequence or end() if last element is deleted.
    //size_type erase(key_type); returns the no. of elements deleted.
    //iterator erase(iterator first, iterator last) // deletes the range [first, last) and returns last.

    //Let's look at find function. Fairly simple, it will return you the iterator to the element or end() if element is
    //not found. Similarly, you have functions count(), lower_bound(), upper_bound() and equal_range() as defined for
    //set and multiset. Note that the find function also just like erase takes as argument the key for that index.
    //Here we are using index 0, for which the key is the entire object.
    typedef boost::multi_index::nth_index<EmployeeTable, 0>::type::iterator ITERATOR_BY_ID;
    typedef boost::multi_index::nth_index<EmployeeTable, 1>::type::iterator ITERATOR_BY_HOME_PHONE;
    typedef boost::multi_index::nth_index<EmployeeTable, 2>::type::iterator ITERATOR_BY_CELL_PHONE;
    typedef boost::multi_index::nth_index<EmployeeTable, 3>::type::iterator ITERATOR_BY_FULL_NAME;
    typedef boost::multi_index::nth_index<EmployeeTable, 4>::type::iterator ITERATOR_BY_FAMILY_GIVEN_NAME;
    typedef boost::multi_index::nth_index<EmployeeTable, 5>::type::iterator ITERATOR_BY_FAMILY_NAME;

    typedef boost::multi_index::nth_index<EmployeeTable, 0>::type INDEX_BY_ID;
    typedef boost::multi_index::nth_index<EmployeeTable, 1>::type INDEX_BY_HOME_PHONE;
    typedef boost::multi_index::nth_index<EmployeeTable, 2>::type INDEX_BY_CELL_PHONE;
    typedef boost::multi_index::nth_index<EmployeeTable, 3>::type INDEX_BY_FULL_NAME;
    typedef boost::multi_index::nth_index<EmployeeTable, 4>::type INDEX_BY_FAMILY_GIVEN_NAME;
    typedef boost::multi_index::nth_index<EmployeeTable, 5>::type INDEX_BY_FAMILY_NAME;

    INDEX_BY_ID& id_index = et.get<0>();
    EmployeeDetails e(5, "Shweta", "Sethi", "55555555", "9811207096");
    ITERATOR_BY_ID iter = id_index.find(e);
    cout << "\n\nFind Operation:\n";
    if(iter == id_index.end()) 
        cout << "No item found" << endl;
    else
        cout << "Employee details found " << *iter << endl;

    // Let's look at the important "replace" and "modify" functions.
    // Both replace and modify do the same job, but differently, You need to decide which one you want to use
    // based on your need.
    // The replace function has constant time complexity if the replacement does not involve any rearrangement.
    // But if replace fails, it will return false and the MIC will not be affected in any way.
    // The replace function takes an iterator to the object to be changed as first parameter and the new object as the
    // second parameter. So first we'll use find to get an iterator to the element, followed by replace.
    cout << endl << "Replace function: \n";
    EmployeeDetails empCopy = *iter; //Shweta Sethi, //Making a copy of the object
    empCopy.cell_phone_number = "+919811207096"; //change cell phone number
    empCopy.home_phone_number = "22222"; //change cell phone number
    if(id_index.replace(iter, empCopy)) { //Second copy created. This is the downside of replace, you have to create two copies of the object. So if copying is expensive in you case, consider using modify. 
        cout << "Object modified: new object = " << *iter << endl; //Note the good thing, the iterator is still valid. Also this function is exception safe. So u must consider using it.
    } else {
        cout << "Object NOT modified"<< endl;
    }

    //Modify. The modify function syntax is similar to replace. First parameter is same, but second parameter is a
    //function object which takes as parameter "a reference to the element". So no need to create copies of object like
    //in replace. In the function object, you can modify the fields of the element.
    //Now modify is different in the following way. If a collision occurs, the entire element is removed from the
    //container. and the function returns false. Otherwise, there is another version which takes another function object
    //(as 3rd parameter) which will be used in case of failure. If this also fails, the element is erased.
    //Lets now try to modify the "Shewta Sethi" record and change the cell phone number to something unique.
   if(id_index.modify(iter, change_cell_phone_no("09811207096"))) {
       cout << "Record modified: " << *iter << endl; //This should be executed.
   } else {
        cout << "Modify failed:\n MIC now looks like" << endl;
        std::copy(id_index.begin(), id_index.end(), ostream_iterator<EmployeeDetails>(cout, "\n"));
   }

   #if 0
   if(id_index.modify(iter, change_cell_phone_no("82984850"))) {
       cout << "Record modified: " << *iter << endl; //This should fail.
   } else {
        cout << "Modify failed:\n MIC now looks like" << endl; //This should be executed.
        std::copy(id_index.begin(), id_index.end(), ostream_iterator<EmployeeDetails>(cout, "\n"));
   }
   #endif

   #if 1
   if(id_index.modify(iter, change_cell_phone_no("82984850"), changeBackTo_old_cell_phone_no("00919811207096"))) {
       cout << "Record modified: " << *iter << endl; //This should execute.
        std::copy(id_index.begin(), id_index.end(), ostream_iterator<EmployeeDetails>(cout, "\n"));
   } else {
        cout << "Modify failed:\n MIC now looks like" << endl; 
        std::copy(id_index.begin(), id_index.end(), ostream_iterator<EmployeeDetails>(cout, "\n"));
   }
   #endif

   //So in summary
   //Behavior of the different updating mechanisms.
   /*     updating function		If there is a collision...
            replace(it,x)	        replacement does not take place.
            modify(it,mod)	        the element is erased.
            modify(it,mod,back)	        back is used to restore the original conditions. (If back throws, the element is erased.)
   */
    return 0;
}

/* Next let us see if all of this is stored in a smart pointer. */
