// We'll demonstrate command_line_parser.extra_parser() here. 

#include <iostream>
#include <string>
#include <utility>
#include <boost/program_options.hpp>

namespace po = boost::program_options;
using std::string;

// boost::program_options will call this function for each command line parameter separately.
std::pair<std::string, std::string> reg_foo(const std::string& s) {
    if(s.find("-f") == 0) {
       if(s.substr(2, 3) == "no-") {
           return std::make_pair(s.substr(5), string("false"));
       } else {
           return std::make_pair(s.substr(2), string("true"));
       }
    } else {
        //The command_line_parser class has two c'tors
        //one is simple (int argc, char** argv)
        //second is command_line_parser(std::vector <string>)
        return std::make_pair(std::string(), std::string());
    }
}

int main(int argc, char* argv[]) {
    
    po::options_description desc("Allowed Options");
    desc.add_options() 
         ("help", "print this help message")
         ("foo", po::value<std::string>(), "just an option")
         ("bar", po::value<std::string>(), "the bar option");

    po::variables_map vm;
    po::store(po::command_line_parser(argc, argv).options(desc).extra_parser(&reg_foo).allow_unregistered().run(), vm);
    po::notify(vm);

    if(vm.count("help")) {
       std::cout << desc << std::endl;
       return 0;
    }
    if(vm.count("foo")) {
        std::cout << "option foo has value: " << vm["foo"].as<std::string>() << std::endl;
        return 0;
    }
    if(vm.count("bar")) {
        std::cout << "bar options is: " << vm["bar"].as<string>() << std::endl;
    }

    return 0;
}

/*
 * Lets say you want to pass an argument of type -fbar or -fno-bar (gcc compiler has many such options),
 * then does program_options supoprt it.. What will you give in the add_options() for such an option.
 * I dont think it is possible right now. So you have the option of calling your own custom parser as 
 * shown above.
 */
