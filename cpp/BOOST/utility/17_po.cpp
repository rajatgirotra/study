// We'll demonstrate how to use collect_unrecognized options
// command_line_parser.run() functions returns:
// basic_parsed_options<charT> run();
// Then we use the options public member variable of this class as shown.

#include <iostream>
#include <string>
#include <vector>
#include <boost/program_options.hpp>
#include <algorithm>

namespace po = boost::program_options;
using std::string;

int main(int argc, char* argv[]) {
    
    po::options_description desc("Allowed Options");
    desc.add_options() 
         ("help", "print this help message")
         ("foo", po::value<std::string>(), "just an option");

    po::variables_map vm;
    po::parsed_options parsed = po::command_line_parser(argc, argv).options(desc).allow_unregistered().run();
    po::store(parsed, vm);
    po::notify(vm);

    if(vm.count("help")) {
       std::cout << desc << std::endl;
       return 0;
    }
    std::vector<string> additionalParameters;

    additionalParameters = po::collect_unrecognized(parsed.options, po::exclude_positional);

    std::copy(additionalParameters.begin(), additionalParameters.end(), std::ostream_iterator<string>(std::cout, "\n"));

    return 0;
}
