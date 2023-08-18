#include <iostream>
#include <string>
#include <ranges>
#include <concepts>
#include <memory>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <tuple>
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/identity.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/mem_fun.hpp>
#include <boost/multi_index/global_fun.hpp>
#include <boost/multi_index/composite_key.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/hashed_index.hpp>
using namespace std;
namespace rng = std::ranges;
namespace vws = std::views;



struct Employee {
    int m_id;
    string m_firstName;
    string m_lastName;

    Employee(int id, string fname, string lname) : m_id(id), m_firstName(std::move(fname)), m_lastName(std::move(lname)) {
    }

    auto operator <=> (const Employee& rhs) const noexcept {
        return m_id <=> rhs.m_id;
    }

    bool operator == (const Employee& rhs) const noexcept {
        return m_id == rhs.m_id;
    }

    friend ostream& operator << (ostream& os, const std::shared_ptr<Employee>& rhs) {
        os << "Employee: (" << rhs->m_id << ", " << rhs->m_firstName << ", " << rhs->m_lastName << ")";
        return os;
    }
};

int main() {
    using EmployeeSet = boost::multi_index_container<std::shared_ptr<Employee>,
                          boost::multi_index::indexed_by <
                            boost::multi_index::ordered_non_unique< boost::multi_index::identity<Employee>>,
                              boost::multi_index::hashed_non_unique<
                                boost::multi_index::composite_key<
                                  std::shared_ptr<Employee>,
                                  BOOST_MULTI_INDEX_MEMBER(Employee, string, m_firstName),
                                  BOOST_MULTI_INDEX_MEMBER(Employee, string, m_lastName)
                                >
                              >
                            >
                        >;

    EmployeeSet es;
    auto& id_index = es.get<0>();

    auto empRajat = std::make_shared<Employee>(10, "Rajat", "Girotra");

    auto res = id_index.insert(empRajat);
    if(res.second) {
        cout << "Inserted " << *(res.first) << endl;
    }

    auto empRajat2 = std::make_shared<Employee>(1, "Rajat", "Girotra");
    auto res2 = id_index.insert(empRajat2);
    if(res2.second) {
        cout << "Inserted " << *(res2.first) << endl;
    } else {
        cout << "Failed to insert " << *(res2.first) << endl;
    }

    auto& hash_index = es.get<1>();
    auto empIter = hash_index.find(std::make_tuple("Rajat", "Girotra"));
    if(empIter != hash_index.end()) {
        cout << "Found " << *(empIter) << endl;
    }

    auto range = hash_index.equal_range(std::make_tuple("Rajat", "Girotra"));
    auto [rFirst, rSecond] = range;
    while(rFirst != rSecond) {
        cout << "Found via equal range " << *(rFirst) << endl;
        ++rFirst;
    }
}