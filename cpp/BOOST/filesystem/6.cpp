/*
Next let us try to know a bit more about the "path" class. 

1] It can be constructed with const char*, std::string, or std::wstring, i.e. it also supports wide character string or i18n.
2] It can also be constructed using iterators, as you will see.

This is possible coz it has template constructors.

template <typename Source>
   path(const Source& src); --> Source could be const char*, std::string or std::wstring

template <typename InputIterator>
   path(InputIterator start, InputIterator end)
*/

#include <iostream>
#include <string>
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>  // Note this include to use boost::filesystem::ofstream class.
#include <fstream>
#include <vector>
using namespace std;

int main() {
	std::string narrow_string("smile2");
	std::wstring wide_string (L"smile2\u263A");

	vector<char> narrow_vector;
	vector<wchar_t> wide_vector;

	narrow_vector.push_back('s');
	narrow_vector.push_back('m');
	narrow_vector.push_back('i');
	narrow_vector.push_back('l');
	narrow_vector.push_back('e');
	narrow_vector.push_back('3');

	wide_vector.push_back(L's');
	wide_vector.push_back(L'm');
	wide_vector.push_back(L'i');
	wide_vector.push_back(L'l');
	wide_vector.push_back(L'e');
	wide_vector.push_back(L'3');
	wide_vector.push_back(L'\u263A');

	// The ofstream class c'tor takes a path object. Passing an std::string,
	//or std::wstring or const char* works coz we have the template c'tor defined above.
	{ boost::filesystem::ofstream f("smile"); }
	{ boost::filesystem::ofstream f(L"smile\u263A"); }
	{ boost::filesystem::ofstream f(narrow_string); }
	{ boost::filesystem::ofstream f(wide_string); }
	{ boost::filesystem::ofstream f(narrow_vector); }
	{ boost::filesystem::ofstream f(wide_vector); }

	narrow_vector.pop_back();
	narrow_vector.push_back('4');

	wide_vector.pop_back();
	wide_vector.pop_back();
	wide_vector.push_back(L'4');
	wide_vector.push_back(L'\u263A');

	{boost::filesystem::ofstream f(boost::filesystem::path(narrow_vector.begin(), narrow_vector.end())); }
	{boost::filesystem::ofstream f(boost::filesystem::path(wide_vector.begin(), wide_vector.end())); }

	return 0;
}