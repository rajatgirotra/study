#include "soapH.h"  // contains functions for reading, writing, creating objects and class definitions for your C/C++ object.
#include "ns1.nsmap" // auto generated namespace array.

int main(int argc, char *argv[]) {
    // The first thing to do is create a soap object. All functions in soapH.h will require a pointer to soap object.
    auto* poSoap = soap_new();

    // create a default object of your generated class
    ns1__employee boss;
    boss.name = "Jane Doe";
    boss.ID = 123;
    
    ns1__employee temp;
    
    
    return 0;
}

