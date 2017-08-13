//
// Created by rajatgirotra on 12/8/17.
//
#include "utils.hpp"
#include <boost/regex.hpp>
#include <string>
using std::string;

bool wildcard_match(const std::string& source, const std::string& pattern) {
    return boost::regex_match(source, boost::regex(pattern));
}

