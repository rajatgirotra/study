/*
 * Here we go one step further.. Just like you can parse command line options
 * you can also parse options in a config file. Based on how you configure things, 
 * options specified both on command line and config file can override or compose each other.
 *
 * Also we will see how we can combine two or more options_description objects together.
 * Let us see these things
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
    std::copy(seq.begin(), seq.end(), ostream_iterator<T>(os, "\n"));
    return os;
}


int main(int argc, char** argv) {

    int opt = 0;
    string configFile;

    // Generic options that can only be specified on the command line
    po::options_description generic("Generic Options");
    generic.add_options()
         //Simple help message. Should be part of every program.
         ("help", "print this help message")
         //Config file name: Default is "multiple_sources.cfg".
         ("config,c", po::value<string>(&configFile)->default_value("multiple_sources.cfg"), "name of configuration file")
         //verbose option
         ("version,v", "print version string");

    //Options that are allowed both on command line and config file.
    po::options_description config("Configuration");
    config.add_options()
          //Optimization level
          ("optimization", po::value<int>(&opt)->default_value(10), "optimization level")
          //include paths. composing() means that this option from multiple sources (command line and config file) can be specified and all will be merged.
          ("include-path,I", po::value<vector <string> >()->composing(), "include path");

    // Hidden options, will be allowed both on the command line and config file, but will not be shown to the user
    // in the help message.
    po::options_description hidden("Hidden Options");
    hidden.add_options()
           //input files
           ("input-file", po::value<vector<string> > (), "input files");

    po::options_description cmdline_options;
    cmdline_options.add(generic).add(config).add(hidden); // See how various options_description objects are combined.

    po::options_description config_options;
    config_options.add(config).add(hidden);

    po::options_description visible("Allowed Options");
    visible.add(generic).add(config);

    po::positional_options_description p;
    p.add("input-file", -1);

    //Read in command line options in the variables_map
    po::variables_map vm;
    po::store(po::command_line_parser(argc, argv).options(cmdline_options).positional(p).run(), vm);
    po::notify(vm);

    //Now read in config file options.
    ifstream ifs(configFile.c_str());
    if(!ifs) {
       cout << "Could not open config file: " << configFile << endl;
       return 0;
    } else {
        po::store(po::parse_config_file(ifs, config_options), vm);
    }


    if(vm.count("help")) {
        cout << visible << endl; // Show only visible options
        return 0;
    }
    if(vm.count("version")) {
        cout << "Multiple sources example, version 1.0\n";
        return 0;
    }
    if(vm.count("include-path")) {
        cout << "Include paths: " << vm["include-path"].as<vector <string> >();
    }
    if(vm.count("input-file")) {
        cout << "Input files: " << vm["input-file"].as<vector <string> >();
    }
    cout << "Optimization level set to: " << vm["optimization"].as<int>() << endl;
    return 0;
}


/* The default syntax of the config file is:
 * name = value, and any line beginning with a # is treated as a comment.
 *
 * A line in the form:
 * [section name]
 * introduces a new section in the configuration file.
 * The option names are relative to the section names, so the following configuration file part:
 *
 * [gui.accessibility]
 *  visual_bell=yes
 *
 * is equivalent to
 * 
 * gui.accessibility.visual_bell=yes
 *     
 * Also note that by default and option value read first will take precedence. So if optimization option is specified
 * both on the command line and the config file, then the value on command line will take precedence, as that is read
 * first according to the program.
 */
