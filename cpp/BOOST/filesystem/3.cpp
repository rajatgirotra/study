/*
Ok, boost::filesystem provides a template class
directory_iterator which is basically an input iterator. You create an object of this class
by passing a path object which refers to a directory. When you iterator using this object, the iterator
returns you an object of class directory_entry(), which basically contains two member variables.

path : containing the actual filename of some file in that directory
file_status: Containing type and permissions of this file.

Since directory_iterator() is an input_iterator() type as specified by the C++ standard, the end iterator is 
constructed using an empty argument list.

directory_iterator() --> An end iterator() used for terminating condition.

Let us now see it in action. Also we'll pass a path argument to directory_iterator() which does not refer to a directory
to see what happens.
*/

#include <iostream>
#include <boost/filesystem.hpp>
#include <algorithm>
#include <iterator>
using std::cout;
using std::endl;
using std::copy;

int main(int argc, char* argv[]) {
	if(argc < 2) {
		cout << "Usage:\n";
		cout <<"\t./a.out <directoryPath>\n";
		return 1;
	} else {
		const boost::filesystem::path p(argv[1]);
		if(boost::filesystem::is_directory(p)) {
			try {
				cout << "Path " << argv[1] << " is a directory path. Iterating now...\n";
				copy(boost::filesystem::directory_iterator(p), boost::filesystem::directory_iterator(),
					std::ostream_iterator<boost::filesystem::directory_entry>(cout, "\n"));
			} catch (const boost::filesystem::filesystem_error& e) {
				cout <<"Exception caught: " << e.what() << endl;
			}
		} else {
			//Not a directory
			cout << "Path " << argv[1] << " is not a directory path\n";
		}
	}
	return 0;
}

/*
When we created directory_iterator() with an invalid path object, i got an exception:

Exception caught: boost::filesystem::directory_iterator::construct: The directory name is invalid: "C:\Documents and Settings\1458615\Desktop\Backup of Singapore_claim_form.xlk"

Next we'll see how to use the directory_entry() object to just print the filename, instead of the whole path.
*/