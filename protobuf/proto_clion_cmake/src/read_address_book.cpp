#include "addressbook.pb.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

void print_address_book(const auto& ab) {
    cout << "Address_book size: " << ab.people_size() << endl;
    for(int i = 0; i < ab.people_size(); ++i) {
        const auto& person = ab.people(i);
        cout << "Person name: " << person.name() << endl;
        cout << "Person id: " << person.id() << endl;
        cout << "Person email: " << person.email() << endl;
        cout << "Phone numbers: " << person.phones_size() << endl;
        for (int j = 0; j < person.phones_size(); ++j) {
            const auto& pn = person.phones(j);
            const auto& type_str = ::tutorial::Person_PhoneType_Name(pn.type());
            cout << "Phone number: " << pn.number() << "   type: " << type_str << endl;
        }
        cout << "------------------------------------------------------------------";
    }
}

int main(int argc, char* argv[]) {
    // Verify that protocol headers are compatible with the libprotobuf library
    GOOGLE_PROTOBUF_VERIFY_VERSION;

    // create an empty address book
    tutorial::AddressBook address_book;

    // read address book
    fstream in(argv[1], ios::in|ios::binary);
    if(!address_book.ParseFromIstream(&in)) {
        cout << "Failed to read address book\n";
        return -1;
    }

    in.close();

    print_address_book(address_book);

    ::google::protobuf::ShutdownProtobufLibrary();
     
    return 0;
}
