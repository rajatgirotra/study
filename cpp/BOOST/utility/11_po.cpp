/*
 * How to use boost::program_options
 */

#include <iostream>
#include <string>
#include <boost/program_options.hpp>

namespace po = boost::program_options;
using namespace std;

int main(int argc, char** argv) {

    /* First create an options_description object passing the description */
    /* Then use the add_options() function to add allowable options. */
    /* add_options() returns a options_description_easy_init object which has:
     * options_description_easy_init& operator(const char* name, const value_semantic*, const char* value) and
     * options_description_easy_init& operator(const char* name,  const char* value)
     * So now the following will make sense.
     */

    po::options_description desc("Allowed Options");

    desc.add_options()
        ("help" , "Prints this help message") //Actual Option on the command line should be --help
        ("compressionLevel" , po::value<int>(), "Specifies the desired compression level"); //Actual Option on the command line is --compressionLevel
    /* Note that po::value() function returns a pointer to a typed_value<T> object which derives from value_semantic
     * indirectly and provides some good functions. We will use it in the next example. */

    /* Next you declare a variables_map object which holds the actual argument values. */
    po::variables_map vm;

    /* No populate the variables map. So parse the command line (argc, argv) according to desc object and then store into
     * vm. Quite straight forward isn't it. :-) 
     * The parse_command_line() function is just a wrapper over the command_line_parser class which handles all the parsing.
     * the parse_command_line() function creates an object of command_line_parser and calls its run() method.
     * At the moment I dont know what notify(vm) does but its mandatory. */
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    /* The po::variables_map actually derives from an std::map<string, variable_value> 
     * where the key to the map is the option name and the value is the options argument
     */
    if(vm.count("help")) {
        cout << desc << endl; // ok, remember that the options_description object has an ostream opeartor to print itself.
        return 1;
    }

    if(vm.count("compressionLevel")) {
        cout << "Compression level set to " << vm["compressionLevel"].as<int>() << endl;
    } else {
        cout << "Compression level is not set" << endl;
    }

    return 0;
}
