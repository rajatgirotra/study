#include <iostream>
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/identity.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/sequenced_index.hpp>
#include <boost/multi_index/mem_fun.hpp>
#include <boost/multi_index/global_fun.hpp>
#include <boost/multi_index/composite_key.hpp>
#include <boost/shared_ptr.hpp>
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

    //New change.
    friend ostream& operator << (ostream& os, const boost::shared_ptr<EmployeeDetails>& rhs)
    {
       os << "Id: " << rhs->id << "  Name: " << rhs->given_name << " " << rhs->family_name
          << "  Home Phone: " << rhs->home_phone_number << "  Cell Phone: " << rhs->cell_phone_number;
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

//New Change
typedef boost::shared_ptr<EmployeeDetails> ITEM;

struct my_extractor {

    typedef string result_type;
    result_type operator() (const EmployeeDetails& ed) {
        return ed.family_name;
    }

    //New change
    result_type operator() (const ITEM& item) {
        return item->family_name;
    }
};


typedef boost::multi_index_container < ITEM, //New Change
            indexed_by <
                ordered_unique < identity <EmployeeDetails> >, 
                ordered_non_unique < BOOST_MULTI_INDEX_MEMBER(EmployeeDetails, std::string, home_phone_number) >,
                ordered_unique < BOOST_MULTI_INDEX_CONST_MEM_FUN(EmployeeDetails, const std::string&, getCellPhoneNumber) >,
                ordered_non_unique < global_fun < const EmployeeDetails&, string , EmployeeDetails::fullName > >,
                ordered_non_unique < composite_key < EmployeeDetails,
                                                     BOOST_MULTI_INDEX_MEMBER(EmployeeDetails, string, family_name),
                                                     BOOST_MULTI_INDEX_MEMBER(EmployeeDetails, string, given_name)
                                     >,
                                     composite_key_compare<
                                         std::greater<string>,
                                         std::less<string>
                                     >
                >,
                ordered_non_unique < my_extractor >
            >
        > EmployeeTable;


struct change_cell_phone_no {
       string newNo;

       change_cell_phone_no(const string& pNewNo) : newNo(pNewNo) {}

       void operator() (ITEM& ed) { //New Change
           ed->cell_phone_number = newNo;
       }
   }; 

struct changeBackTo_old_cell_phone_no {
       string newNo;
       changeBackTo_old_cell_phone_no(const string& pNewNo) : newNo(pNewNo) {}

       void operator() (ITEM& ed) {
           ed->cell_phone_number = newNo;
       }
   }; 


int main()
{

    EmployeeTable et;

    typedef EmployeeTable::nth_index<0>::type::iterator Iterator;
    std::pair<Iterator, bool> insertResult;

    ITEM item;
    item.reset(new EmployeeDetails(1, "Rajat", "Girotra", "92716159", "82984850")); //New change

    insertResult = et.get<0>().insert(item);
    if(insertResult.second == true) {
        cout << "Inserting EmployeeDetails: " << **insertResult.first << " into MIC" << endl; //New Change
    }
    item.reset(new EmployeeDetails(1, "Rajat", "Girotra", "92716159", "82984850"));
    insertResult = et.get<0>().insert(item);
    if(insertResult.second == false) {
        cout << "Inserting EmployeeDetails failed/banned by existing element: " << **insertResult.first << endl;
    }

    boost::multi_index::nth_index<EmployeeTable, 0>::type::iterator ic0;

    item.reset(new EmployeeDetails(2, "Vidhu", "Ahuja", "92716159", "86066774"));
    et.get<1>().insert(item);
    item.reset(new EmployeeDetails(3, "Sudesh", "Ahuja", "25460995", "9871494404"));
    et.get<2>().insert(item);
    item.reset(new EmployeeDetails(4, "Vijay", "Ahuja", "25460995", "9818125914"));
    et.get<3>().insert(item);
    item.reset(new EmployeeDetails(5, "Shweta", "Sethi", "55555555", "9811207096"));
    et.get<4>().insert(item);
    item.reset(new EmployeeDetails(6, "Jitin", "Sethi", "55555555", "9811267202"));
    et.get<5>().insert(item);

    const EmployeeTable::nth_index<2>::type& cell_index = et.get<2>();
    std::copy(cell_index.begin(), cell_index.end(), ostream_iterator<ITEM>(cout, "\n")); //New change.

    cout << endl;
    //et.get<2>().erase("9871494404"); 
    //et.get<1>().erase("92716159");
    std::copy(cell_index.begin(), cell_index.end(), ostream_iterator<ITEM>(cout, "\n")); //New change.

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
    ITERATOR_BY_ID iter = id_index.find(e); // No Change.
    cout << "\n\nFind Operation:\n";
    if(iter == id_index.end()) 
        cout << "No item found" << endl;
    else
        cout << "Employee details found " << **iter << endl; //No Change.

    cout << endl << "Replace function: \n";
    item.reset(new EmployeeDetails(**iter));
    item->cell_phone_number = "+919811207096";
    item->home_phone_number = "22222"; 
    if(id_index.replace(iter, item)) { 
        cout << "Object modified: new object = " << **iter << endl;
    } else {
        cout << "Object NOT modified"<< endl;
    }

   if(id_index.modify(iter, change_cell_phone_no("09811207096"))) {
       cout << "Record modified: " << **iter << endl; //This should be executed.
   } else {
        cout << "Modify failed:\n MIC now looks like" << endl;
        std::copy(id_index.begin(), id_index.end(), ostream_iterator<ITEM>(cout, "\n"));
   }

   #if 0
   if(id_index.modify(iter, change_cell_phone_no("82984850"))) {
       cout << "Record modified: " << **iter << endl; //This should fail.
   } else {
        cout << "Modify failed:\n MIC now looks like" << endl; //This should be executed.
        std::copy(id_index.begin(), id_index.end(), ostream_iterator<ITEM>(cout, "\n"));
   }
   #endif

   #if 1
   if(id_index.modify(iter, change_cell_phone_no("82984850"), changeBackTo_old_cell_phone_no("00919811207096"))) {
       cout << "Record modified: " << **iter << endl; //This should execute.
        std::copy(id_index.begin(), id_index.end(), ostream_iterator<ITEM>(cout, "\n"));
   } else {
        cout << "Modify failed:\n MIC now looks like" << endl; 
        std::copy(id_index.begin(), id_index.end(), ostream_iterator<ITEM>(cout, "\n"));
   }
   #endif

   ITERATOR_BY_CELL_PHONE it;
   INDEX_BY_CELL_PHONE& cellIndex = boost::multi_index::get<2>(et);
   it = cellIndex.find("86066774");
   if(it != cellIndex.end()) {
       cout << "\nChanging phone no for Vidhu\n";
      item.reset(new EmployeeDetails(**it));
      item->cell_phone_number = "98869763";
      cellIndex.replace(it, item);
      std::copy(cellIndex.begin(), cellIndex.end(), ostream_iterator<ITEM>(cout, "\n"));
   }

    return 0;
}
