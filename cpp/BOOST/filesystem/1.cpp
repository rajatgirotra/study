/*
The boost filesystem library allows you to manipulate files and directories on your filesystem
The most important class here in this library is called "path". You'll see and learn about it as you progress

The first program here is to get the size of a file which is passed as argument.
*/

#include <iostream>
#include <boost/cstdint.hpp>
#include <boost/filesystem.hpp>
using std::cout;
using std::endl;
using std::cerr;

/* The function that provides the size of a file is file_size(const char*) */

int main(int argc, char* argv[]) {
	if(argc < 2) {
		cout << "Usage:\n";
		cout<< "\t./a.out <filename>]\n";
		return 1;
	}
	
	else {
		try {
			boost::uintmax_t sz = boost::filesystem::file_size(argv[1]);
			cout << "Filename: " << argv[1] << "... Size: " << sz << endl;
		} catch (const boost::filesystem::filesystem_error& e) {
			cerr << "Exception caught: " << e.what() << endl;
		}
	}

	return 0;
}

/*
The API is defined in boost::filesystem as

uintmax_t file_size(const path& p);

Now, we include <boost/cstdint.hpp> to get the definition of uintmax_t which could be unsigned 64 bit or 32 bit
value depending on your machine.

Also, the "path" class defines a c'tor which take a "const char*" argument, so passing const char* as argument
to file_size() works.

Try to pass a directory as argument: You'll see an exception that the request is not supported.
So as a good practice always use try ... catch block when using boost::filesystem API's
*/
