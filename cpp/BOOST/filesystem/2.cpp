/*
Here we will explore some more API's of boost::filesystem. Most of these are self-explantory.

bool exists(const path& p)
bool is_directory(const path& p)
bool is_regular_file(const path& p)
*/

#include <iostream>
#include <boost/filesystem.hpp>
using std::cout;
using std::cerr;
using std::endl;

int main(int argc, char* argv[]) {
	//Make sure an argument is passed.
	if(argc < 2) {
		cout << "Usage:\n";
		cout << "\ta.out <pathName>\n";
		return 1;
	} else {
		//Create a path object.
		const boost::filesystem::path p(argv[1]);

		//Check that the path is valid.
		if(exists(p)) {
			try {
				if(boost::filesystem::is_regular_file(p)) {
					cout << "Path " << argv[1] << " is a regular file\n";
				} else if (boost::filesystem::is_directory(p)) {
					cout << "Path " << argv[1] << " is a directory\n";
				} else {
					cout << "Path " << argv[1] << " is neither a regular file nor a directory";
				}
			} catch (const boost::filesystem::filesystem_error& e) {
				cout << "Exception caught: " << e.what() << endl;
			}
		} else {
			//Invalid path. Log an error and return;
			cout << "Path: " << argv[1] << " does not exist\n";
		}
	}
	return 0;
}

/*
This one is fairly simple & straight forward.
Next we'll see how to iterate over files in a given directory.
*/