#include "OptionProcessor.hpp"
#include "Switch.hpp"
#include <iostream>
using namespace std;
using namespace rg::util;

const Switch program_options[] = {
        {"help", "generate help message on the command line", SwitchArgument::not_required, 'h'},
        {"config_file", "full path to config file ",          SwitchArgument::required,     'c', "config-file"},
        {"log_file", "full path to log file ",                SwitchArgument::optional,     'l', Switch::NO_LONG_SWITCH, "1234"},
};


int main(int argc, char** argv) {
    try {
        OptionsProcessor::parse(argc, argv);
        cout  << "OptionsProcessor done\n";
    } catch(const std::exception& e) {
        cerr << "Exchange caught: " << e.what();
    }
}
