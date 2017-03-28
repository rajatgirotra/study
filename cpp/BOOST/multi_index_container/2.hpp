#ifndef _EMPLOYEE_HPP_
#define _EMPLOYEE_HPP_ 

#include <string>
#include <iostream>

struct Employee {
        int id;
        std::string name;

        //Sorting criteria.
        inline bool operator < (const Employee& emp) const {
            return id < emp.id;
        }

        //C'tor
        Employee(const int& pId, const std::string& pName) : id(pId), name(pName) 
        {}

        //ostream operaror
        friend std::ostream& operator << (std::ostream& os, const Employee& e) {
            os << "Id: " << e.id << "    Name: " << e.name;
            return os;
        }
};

#endif //_EMPLOYEE_HPP_
