#include <iostream>
#include <boost/program_options.hpp>
#include <boost/exception/all.hpp>
using namespace std;
namespace po = boost::program_options;

int main(int argc, char *argv[]) {
    int cl {};
    po::options_description desc("Allowed Options");
    desc.add_options()
    ("help", "Print this help message")
        ("compressionLevel, c", po::value<int>(&cl)->default_value(10)/*->value_name("SomeNewValue")*/, "compression level, defaults to 10")
        ("email", po::value<string>()->multitoken(), "list of email ids")
        ("mandatory", po::value<string>()->required(), "mandatory value");

    po::variables_map vm;
    po::store(po::command_line_parser(argc, argv).options(desc).run(), vm);


    if(vm.count("help")) {
        cout << desc << endl;
        return 0;
    }

    try {
       po::notify(vm);
    } catch(const boost::exception& e) {
        cerr << boost::diagnostic_information(e) << endl;
    }

    cout << "compression level is set to: " << cl << endl;
    cout << "compression level is set to: " << vm["compressionLevel"].as<int>() << endl;

    if(vm.count("email")) {
        cout << "email ids: " << vm["email"].as<string>() << endl;
    }

    return 0;
}
