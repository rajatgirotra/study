/*
Ok Lets now get to a slightly complex scenario.

Native and Generic Format : Every path or filename can be specified in either the native or generic format.

Generic Format : Uses "/" (frontslashes, or simply slashes) as directory separaters. This format is used by POSIX like operating systems
such as Unix etc and also called as URL format.

Native format : The directory separater is defined by the operating system. For Windows, back-slash is used, and on linux, slashes are used.
So a windows path "/foo/bar\baz.txt" is valid, as it contains a mix of both generic and native format. Ofcourse, when you represent it in
std::string format in C++, you';; say "/foo/bar\\baz.txt" because of escaping.

The class "path" allows various functions to:

1] Iterate over the path elements : i.e. elements separated by the directory separater.
2] Observers: Functions to retrieve path as strings in either native or generic format
3] Composition & Decomposition : Functions to compose a new path or decompose an existing path
4] Query : General query functions.

We are going to see all of them in action now. 

Also remember, that path always stores the filename internally in the native operating system defined format.

*/

#include <iostream>
#include <boost/filesystem.hpp>
using namespace std;

int main(int argc, char* argv[]) {
	//Make sure arguments are passed.
	if(argc < 2) {
		cout << "Usage:\n";
		cout << "\t./a.out path-portion...\n";
		cout << "Example: ./a.out foo/bar baz.txt\n";
#ifdef BOOST_POSIX_API
		cout << "would display information about the composed path foo/bar/baz.txt\n";
#else
		cout << "would display information about the composed path foo/bar\\baz.txt\n";
#endif
		return 1;
	}

	//Create an empty path object and compose it from the command line arguments passed.
	boost::filesystem::path p; //empty path

	for (int i = 1; argc > 1; --argc) {
		p /= argv[i++]; // The /= overloaded operator composes the path using the native directory separator.
	}

	/* MyFirstProject.exe /tools/apache-ant-1.9.0   bin/ant.bat
	displayed:
		Composed Path:
		Path: "/tools/apache-ant-1.9.0\bin/ant.bat"  //Note the windows backslash used, as I said above.
		make_preferred(): "\tools\apache-ant-1.9.0\bin\ant.bat" 
    */
	cout << "Composed Path: \n";
	cout << "Path: " << p << endl;
	cout << "make_preferred(): " << p.make_preferred() << endl;  // --> make_preferred() always outputs the in native format.

	// Now we'll display the elements of the path */
	cout << "\nelements:\n";
	for(boost::filesystem::path::iterator it = p.begin(); it != p.end(); ++it) {
		cout << "  " << *it << endl; // the path::iterator::value_type is path::string_type which could be either string or wstring.
	}

	 cout  <<  "\nobservers, native format:" << endl;
# ifdef BOOST_POSIX_API
  cout  <<  "  native()-------------: " << p.native() << endl;
  cout  <<  "  c_str()--------------: " << p.c_str() << endl;
# else  // BOOST_WINDOWS_API
	 //In Windows, value_type is wchar_t
	 //and string_type is basic_string<value_type>, so we need to use
	 //wcout when using native() and c_str() functions as these
	 //return string_type and value_type.
  wcout << L"  native()-------------: " << p.native() << endl;
  wcout << L"  c_str()--------------: " << p.c_str() << endl;
# endif

  //Note that the string() and wstring() functions also return the native format.
  //Use the native format when dealing with users or operating system, as they would expect the native format.
  cout  <<  "  string()-------------: " << p.string() << endl;
  wcout << L"  wstring()------------: " << p.wstring() << endl;

  //Use generic format when you want your code to be portable across platforms.
  cout  <<  "\nobservers, generic format:\n";
  cout  <<  "  generic_string()-----: " << p.generic_string() << endl;
  wcout << L"  generic_wstring()----: " << p.generic_wstring() << endl;

  //The decomposition and query functions are rather straight-forward.
  //In C:\tools\ant-1.9.0-bin\bin\ant.bat, C: is root-name. \ is root-directory
  // C:\ is root-path (i.e. concatination of root-name and root-directory)
  //I havent tried but i think on linux, root-name will be empty, root-directory
  //will be /, and root-path will be /. You can try.
  cout  <<  "\ndecomposition:\n";
  cout  <<  "  root_name()----------: " << p.root_name() << '\n';
  cout  <<  "  root_directory()-----: " << p.root_directory() << '\n';
  cout  <<  "  root_path()----------: " << p.root_path() << '\n';
  cout  <<  "  relative_path()------: " << p.relative_path() << '\n';
  cout  <<  "  parent_path()--------: " << p.parent_path() << '\n';
  cout  <<  "  filename()-----------: " << p.filename() << '\n';
  cout  <<  "  stem()---------------: " << p.stem() << '\n';
  cout  <<  "  extension()----------: " << p.extension() << '\n';

  cout  <<  "\nquery:\n";
  cout  <<  "  empty()--------------: " << boolalpha << (p.empty()) << '\n';
  cout  <<  "  is_absolute()--------: " << boolalpha << (p.is_absolute()) << '\n';
  cout  <<  "  has_root_name()------: " << boolalpha << (p.has_root_name()) << '\n';
  cout  <<  "  has_root_directory()-: " << boolalpha << (p.has_root_directory()) << '\n';
  cout  <<  "  has_root_path()------: " << boolalpha << (p.has_root_path()) << '\n';
  cout  <<  "  has_relative_path()--: " << boolalpha << (p.has_relative_path()) << '\n';
  cout  <<  "  has_parent_path()----: " << boolalpha << (p.has_parent_path()) << '\n';
  cout  <<  "  has_filename()-------: " << boolalpha << (p.has_filename()) << '\n';
  cout  <<  "  has_stem()-----------: " << boolalpha << (p.has_stem()) << '\n';
  cout  <<  "  has_extension()------: " << boolalpha << (p.has_extension()) << '\n';

  return 0;
}