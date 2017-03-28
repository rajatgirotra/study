/*
Lets see how to use the directory_entry() object directly.
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
				boost::filesystem::directory_entry de;

				for(boost::filesystem::directory_iterator iter(p); iter != boost::filesystem::directory_iterator();
					++iter) {
						de = *iter;
						cout << "File: " << de.path().filename() << "\n";
				}
				
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