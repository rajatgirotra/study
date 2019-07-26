/*
 * WAP that accepts a python list of strings of words "one", "two", "three" and returns a list of integers by
 * converting from word to number.  You will need py::list object. read its api.
 */
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <boost/python.hpp>
using namespace std;
namespace py = boost::python;

namespace {
    std::unordered_map<string, int64_t> word_to_number;

    void buildMap() {
	word_to_number["zero"] = 0;
	word_to_number["one"] = 1;
	word_to_number["two"] = 2;
	word_to_number["three"] = 3;
	word_to_number["four"] = 4;
	word_to_number["five"] = 5;
	word_to_number["six"] = 6;
	word_to_number["seven"] = 7;
	word_to_number["eight"] = 8;
	word_to_number["nine"] = 9;
	word_to_number["ten"] = 10;
	word_to_number["default"] = -1;
    }

}

vector<int64_t> wtn(vector<string> vec) {
    vector<int64_t> result;
    buildMap();
    for(auto&& item : vec) {
	auto iter = word_to_number.find(item);
	if(iter == word_to_number.end()) {
	    result.emplace_back(-1);
	} else {
	    result.emplace_back(iter->second);
	}
    }
    return result;
}

py::list words_to_numbers(py::list arg) {
    py::list out;
    vector<string> vec;
    for(auto i = 0; i < py::len(arg); ++i) {
        vec.emplace_back(py::extract<string>(arg[i]));
    }
    auto result = wtn(vec); 
    for(auto&& item : result) {
	out.append(item);
    }
    return out;
}

BOOST_PYTHON_MODULE(practice_4_ext) {
    py::def("words_to_numbers", words_to_numbers);
}
