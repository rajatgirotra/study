/*
 * Here we will show that when you run, ./a.out a.cpp
 * Then program options can be configured to think a.cpp as --input-file a.cpp
 *
 * An option which does not have a name is called as a positional option by the library.
 */

#include <iostream>
#include <string>
#include <boost/program_options.hpp>
#include <vector>
#include <fstream>
#include <algorithm>

namespace po = boost::program_options;
using namespace std;

template <typename T>
ostream& operator << (ostream& os, const std::vector<T>& seq) {
    std::copy(seq.begin(), seq.end(), std::ostream_iterator<T>(os, "\n"));
    return os;
}


int main(int argc, char** argv) {

    int level = 0;

    po::options_description desc("Allowed Options");

    desc.add_options()
        ("help" , "Prints this help message")
        /* Can specify --include-path or -I option,
        *  note the value is a vector of string, so we can have multiple such options on the command line
        */
        ("include-path,I", po::value<vector <string> >(), "path to search for include files")
        ("input-file", po::value<vector <string> >(), "file(s) to compile")
        ("compressionLevel" , po::value<int>(&level)->default_value(10), "Specifies the desired compression level"); // Store the value in opt variable after the call to store function.
        // Also the default value is set to 10 if no value is specified.

    // Create a positional option
    po::positional_options_description p;
	//The second argument specifies how many positional arguments will be tagged with the name "input-file". So
	//p.add("input-file", 1); means only the first positional argment will be tagged. -1 means all positional argument will be tagged.
	//p.add("output-file", 2).add("input-file", -1); means the first two positional arguments will be tagged as output-file and all others will be tagged as input-file.
    p.add("input-file", -1);

    /* Next you declare a variables_map object which holds the actual argument values. */
    po::variables_map vm;
    //Note how we use the command_line_parser class below instead of parse_command_line. parse_command_line is just a
    //simple wrapper over command_line_parser, but here we are doing something more complex.
    po::store(po::command_line_parser(argc, argv).options(desc).positional(p).run(), vm);
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
