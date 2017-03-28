/*
 * How to use boost::program_options
 */

#include <iostream>
#include <string>
#include <boost/program_options.hpp>
#include <vector>
#include <fstream>

namespace po = boost::program_options;
using namespace std;

template <typename T>
ostream& operator << (ostream& os, const std::vector<T>& seq) {
    typename vector<T>::const_iterator iter = seq.begin();
    os << endl;
    while (iter != seq.end()) {
        os << *iter++ << endl;
    }
    return os;
}


int main(int argc, char** argv) {

    int level = 0;
    int portNumber = 0;

    po::options_description desc("Allowed Options");

    desc.add_options()
        ("help" , "Prints this help message")

        /* implicit_value() means you can just specify -v or --verbose and it will default to -v 1 or --version 1" */
        ("verbose,v", po::value<int>()->implicit_value(1), "enable detailed logging (optionally specify level)")

        ("include-path,I", po::value<vector <string> >(), "path to search for include files")
        /* Can specify --include-path or -I option,
         *  note the value is a vector of string, so we can have multiple such options on the command line */

        ("input-file", po::value<vector <string> >(), "file(s) to compile")

        ("compressionLevel" , po::value<int>(&level)->default_value(10), "Specifies the desired compression level") // Store the value in opt variable after the call to store function.
        // Also the default value is set to 10 if no value is specified.
        
        ("listen,l", po::value<int>(&portNumber)->default_value(0, "no")->implicit_value(1001), "listen on port number"); // "no" here is just a textual representation of the default value 0.

    /* Next you declare a variables_map object which holds the actual argument values. */
    po::variables_map vm;

    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    /* The po::variables_map actually derives from an std::map<string, variable_value> */
    if(vm.count("help")) {
        cout << desc << endl; // ok, remember that the options_description object has an ostream opeartor to print itself.
        return 1;
    }

    if(vm.count("compressionLevel")) {
        cout << "Compression level set to " << vm["compressionLevel"].as<int>() << endl;
    } else {
        cout << "Compression level is not set" << endl;
    }

    if(vm.count("include-path")) {
       cout << "Include paths set to: " << vm["include-path"].as<vector<string> >() << endl;
    }

    if(vm.count("input-file")) {
       cout << "Input files are " << vm["input-file"].as<vector<string> >() << endl;
    }

    return 0;
}
