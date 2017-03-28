//Demonstrating simple rvalue references for overloading assignment operators.

#include <iostream>
#include <string>
using namespace std;

class Number
{
private:
    static int counter;

public:
    double* poNumber;
    int tag;
    Number(const double& dArg = 6.6) : poNumber(new double(dArg)), tag(++counter)
    {
        cout << "Object created with tag: " << tag <<" ,poNumber: " << poNumber << endl;
    }

    ~Number()
    {
        cout << "Object destroyed with tag: " << tag <<" ,poNumber: " << poNumber  << endl;
        if(poNumber)
        {
            delete poNumber;
            poNumber = 0;
        }
    }

    //Copy c'tor
    Number(const Number& rhs) : tag(++counter)
    {
        poNumber = new double(*rhs.poNumber);
        cout << "Copy of object created with tag: " << tag <<" ,poNumber: " << poNumber << " using tag: " << rhs.tag << endl;
    }

    //Assignment Operator
    Number& operator = (const Number& rhs)
    {
        delete poNumber;
        this->poNumber = new double(*rhs.poNumber);
        cout << "Assignment operator, this tag: " << this->tag <<" ,poNumber: " << poNumber << " ,incoming tag: " << rhs.tag << endl;
        return *this;
    }

    //Move Assignment operator
    Number& operator = (Number&& rhs)
    {
        double* tmp = 0;
        cout << "Move Assignment operator, this tag: " << this->tag <<" ,poNumber: " << poNumber
             << " ,incoming tag: " << rhs.tag << " ,incoming poNumber: " << rhs.poNumber << endl;
        tmp = this->poNumber;
        this->poNumber = rhs.poNumber;
        rhs.poNumber = tmp;
        return *this;
    }
};

int Number::counter = 0;

Number foobar()
{
    return Number(20);
}

int main()
{
    Number n(10);
    n = foobar();
    return 0;
}

