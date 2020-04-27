//Demonstrating simple rvalue references for overloading assignment operators.

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

class Number
{
private:
    static int counter;

public:
    char* poData;
    int tag;
    uint64_t size;
    Number(uint64_t arg = 1024*1024*1024*2ULL) : poData(new char[arg]), tag(++counter), size(arg)
    {
        cout << "Object created with tag: " << tag <<" ,poData: " << static_cast<void*>(poData) << endl;
    }

    ~Number()
    {
        cout << "Object destroyed with tag: " << tag <<" ,poData: " << static_cast<void*>(poData)  << endl;
        if(poData)
        {
            delete[] poData;
            poData = 0;
        }
    }

    //Copy c'tor
    Number(const Number& rhs) : tag(++counter)
    {
        poData = new char[rhs.size];
        cout << "Copy of object created with tag: " << tag <<" ,poData: " << static_cast<void*>(poData) << " using tag: " << rhs.tag << endl;
    }

    //Assignment Operator
    Number& operator = (const Number& rhs)
    {
        delete[] poData;
        this->poData = new char[rhs.size];
        cout << "Copy Assignment operator, this tag: " << this->tag <<" ,poData: " << static_cast<void*>(poData) << " ,incoming tag: " << rhs.tag << endl;
        return *this;
    }

    //Move Assignment operator
    Number& operator = (Number&& rhs)
    {
        cout << "Move Assignment operator, this tag: " << this->tag <<" ,poData: " << static_cast<void*>(poData)
             << " ,incoming tag: " << rhs.tag << " ,incoming poData: " << static_cast<void*>(rhs.poData) << endl;
        std::swap(poData, rhs.poData);
        return *this;
    }
};

int Number::counter = 0;

Number foobar()
{
    return Number();
}

int main()
{
    Number n(10);
    n = foobar();
    return 0;
}

