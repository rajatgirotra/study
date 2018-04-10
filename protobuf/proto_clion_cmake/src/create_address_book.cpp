#include "addressbook.pb.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

void get_person_details(auto person) {
    cout << "Enter person name: ";
    std::getline(cin, *person->mutable_name());
    
    cout << "Enter person id: ";
    auto id{0};
    cin >> id;
    person->set_id(id);

    cin.ignore(256, '\n');

    cout << "Enter email (blank for none): ";
    string email;
    std::getline(cin, email);
    if(!email.empty())
        person->set_email(email);

    while (true) {
        cout << "Enter phone number (blank for none): ";
        string number;
        std::getline(cin, number);
        if(number.empty())
            break;

        // set phone number
        auto phone_number = person->add_phones();
        phone_number->set_number(number);

        cout << "Enter phone number type (mobile, home, work): ";
        string type;
        std::getline(cin, type);
        if (type == "mobile")
            phone_number->set_type(tutorial::Person::MOBILE);
        else if (type == "home")
            phone_number->set_type(tutorial::Person::HOME);
        else if (type == "work")
            phone_number->set_type(tutorial::Person::WORK);
        else {
            cout << "Unknown phone type. Using MOBILE" << endl;
            phone_number->set_type(tutorial::Person::MOBILE);
        }
    }
}

int main(int argc, char* argv[]) {
    // Verify that protocol headers are compatible with the libprotobuf library
    GOOGLE_PROTOBUF_VERIFY_VERSION;

    // create an empty address book
    tutorial::AddressBook address_book;

    get_person_details(address_book.add_people());

    // output serialized address book to file
    fstream out("addressbook.bin", ios::out|ios::trunc|ios::binary);
    if(!address_book.SerializeToOstream(&out)) {
        cout << "Failed to write address book\n";
        return -1;
    }
    out.close();

    ::google::protobuf::ShutdownProtobufLibrary();
     
    return 0;
}
