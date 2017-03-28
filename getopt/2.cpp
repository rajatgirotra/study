#include <iostream>
#include <unistd.h>
using namespace std;

int main(int argc, char* argv[]) {
    cout << "opterr at start: " << opterr << endl;
    cout << "optopt at start: " << optopt << endl;
    cout << "optind at start: " << optind << endl;

    const char*options {};
    // auto rc = getopt(argc, argv, options);
    cout << "opterr after calling getopt(): " << opterr << endl;
    cout << "optopt after calling getopt(): " << optopt << endl;
    cout << "optind after calling getopt(): " << optind << endl;

    // cout << rc << endl;
}
