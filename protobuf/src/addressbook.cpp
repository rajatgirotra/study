#include "addressbook.pb.h"
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;
using tutorial::Person;
using tutorial::Person_PhoneNumber;

int main(int argc, char *argv[]) {

    // Lets see the protobuf API.

    /* Create a default initialized object of type Person */
    Person p;

    cout << "Name:" << endl;
    if (!p.has_name()) {
        cout << "Default Person object has no name" << endl;
        p.set_name(string("Rajat"));
        cout << "after person.set_name(string) : " << p.name() << endl;
        p.set_name("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
        cout << "after person.set_name(const char* value) : " << p.name() << endl;
        p.set_name("ABCDEFGHIJKLMNOPQRSTUVWXYZ", 4);
        cout << "after person.set_name(const char* value, size) : " << p.name() << endl;
        /* release_name() means the function will release ownership of the pointer returned  by
           the function. Also has_name() will return false and name() will return default value.
           So release_name returns a pointer to string here which will have no relation to the "name"
           member after the call */
        auto strPtr = p.release_name();
        cout << "p.release_name(): " << *strPtr << endl;
        delete strPtr;

        /* Mutable returns a pointer to the "name" field and you can also assign to it (if you want to change its value).
         *p.mutable_name() = "SomeNewName". After the call has_name() will return true and name() will return the new value
         */
        p.set_name("Mother");
        cout << "p.mutable_name(): " << *p.mutable_name() << endl;
        *p.mutable_name() = "Father";
        cout << "p.mutable_name(): " << *p.mutable_name() << endl;                                         
    }

    cout << "\nId:" << endl;
    if (!p.has_id()) {
        cout << "Id field is not available" << endl;
        cout << "Id: " << p.id() << endl;  // default value is 0
        p.set_id(100);
        cout << "Id: " << p.id() << endl;
        p.clear_id();
        cout << "Id: " << p.id() << endl;
    }

    cout << "\nEmail is same as name as it is string" << endl;
    cout << "\nPhone Numbers" << endl;
    if (p.phone_size() == 0) {
        cout << "No phone number is in list. Adding now " << endl;
        Person_PhoneNumber n1;
        n1.set_number("123456"); n1.set_type(Person::WORK);
        Person_PhoneNumber n2;
        n2.set_number("991000");
        //*p.mutable_phone(0) = n1;  // this will crash. mutable_size() can only work if index is less than size.
        //*p.mutable_phone(1) = n2;  // this will crash. mutable_size() can only work if index is less than size.
        // so we need to use add_phone() instead of mutable_phone()
        *p.add_phone() = n1;
        *p.add_phone() = n2;
        cout << "After adding two phone numbers, size: " << p.phone_size() << endl;
        auto all_phones = p.phone();
        for (const auto& ph : all_phones) {
            cout << "Number: " << ph.number() << "    Type: " << ph.type() << endl;
        }
        auto tmp = p.phone(1);
        cout << "Second phone number: ";
        cout << "   Number: " << tmp.number() << "    Type: " << tmp.type() << endl;
        // modify first phone number
        cout << "After modifying first phone number" << endl;
        *p.mutable_phone(0) = n2;
        for (const auto& ph : p.phone()) {
            cout << "Number: " << ph.number() << "    Type: " << ph.type() << endl;
        }
    }

    // Some functions on the Message itself (above you looked at fields)
    cout << "IsInitialized(): (are all required fields available?) " << std::boolalpha <<  p.IsInitialized() << endl;
    cout << "DebugString(): (string representation) ";
    cout << p.DebugString() << endl;
    return 0;
}

/* Compile using
gpp -I /home/rajatgirotra/tools/google/protobuf/include addressbook.pb.cc addressbook.cpp -L /home/rajatgirotra/tools/google/protobuf/lib -lprotobuf
*/
