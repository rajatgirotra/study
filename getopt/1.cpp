#include <iostream>
#include <unistd.h>
using namespace std;

// in getopt by GNU, you can specify options (ie -x, -n etc); and arguments to these options.
int main(int argc, char* argv[]) {
    // opterr: by default is non-zero, meaning that if getopt() finds any option that is not expected, it wll print an error on the stderr stream. If set to zero, will not print to stderr, but will return "?" (ascii 63) to indicate that an error has occurred.
    cout << "opterr at start: " << opterr << endl;
    // optopt: if getopt() finds any option that is not expected (eg: say -x), then it store the ascii value of x in optopt. The type is int. By default, it stores "?"
    cout << "optopt at start: " << optopt << endl;
    // optind: will store the index of the next element in argv that will be processed by getopt().
    cout << "optind at start: " << optind << endl;
}
