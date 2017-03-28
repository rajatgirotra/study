/* How to use po::parse_environment() */

#include <iostream>
#include <boost/program_options.hpp>
#include <string>
using namespace std;
namespace po = boost::program_options;

int main(int ac, char** av) {

    po::options_description desc("Allowed Options");
    desc.add_options()
        ("help", "print this help message")
        ("proxy", po::value<string>(), "proxy server IP/Hostname");

    //the program will search for environment variable ABCD_PROXY or ABCD_proxy and will set the proxy option to its
    //value. If both environment variables are present, it is an exception (multiple_occurences).
    //So it is always a good idea to have a sufficiently unique prefix for your program. like here we have ABCD_.
    //In S2BX we have PUMA_
    po::parsed_options parsed = po::parse_environment(desc, "ABCD_");

    po::variables_map vm;
    po::store(parsed, vm);
    po::notify(vm);

    if(vm.count("proxy")) {
       cout << "option proxy set to: " << vm["proxy"].as<string>() << endl;
    } else {
        cout << "option proxy not specified: " << endl;
    }
    return 0;
}
