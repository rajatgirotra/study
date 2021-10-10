/*
 * using filesystem library to fetch all the files in a given directory.
 */
#include <filesystem>
#include <iostream>
#include <iomanip>
using namespace std;
namespace fs = std::filesystem;

void displayDirectoryTree(const fs::path folder_path, [[maybe_unused]] int level = 0) {
    // create a directory iterator over a path identified by the folder_path.
    // the ctor may throw if folder_path is not existent or does not refer to a directory.
    // this directory_iterator does not recurse into sub-directories.
    // an empty directory_iterator() represents the end iterator.
    fs::directory_iterator dir_iter(folder_path);
    for(auto&& entry : dir_iter) {
        // get path string
        const auto filenameString = entry.path().filename().string(); // filename() returns only the filename part
        // entry is of type fs::directory_entry. It must represent a path which must exist on the filesystem.
        // In addition, it stores additional file attributes (hard link count, status, symlink status, file size etc.
        if(entry.is_directory()) {
            // manually recurse sub-directories
            // directory_entry has an "operator const fs::path&()" to get the fs::path it refers to.
            cout << std::setw(level*3) << "" << filenameString << "\n";
            displayDirectoryTree(entry, level+1);
        } else if (entry.is_regular_file()) {
            cout << std::setw(level*3) << "" << filenameString << ", size " << fs::file_size(entry) << " bytes\n";
        } else {
            cout << std::setw(level*3) << "" << filenameString << " [?] " << fs::file_size(entry) << "\n";
        }
    }
}

int main(int argc, char** argv) {
    try {
        // create a fs::path object
        const fs::path pathToShow { argc >= 2 ? argv[1] : fs::current_path() };
        // fs::absolute(fs::path) returns the absolute path as string.
        cout << "listing files in directory: " << fs::absolute(pathToShow) << "\n";
        displayDirectoryTree(pathToShow);
    } catch (const fs::filesystem_error& e) {
        // fs::filesystem_error is the exception thrown by most filesystem operations.
        cerr << "filesystem error! " << e.what() << ", error code: " << e.code() << ", msg: " << e.code().message() << endl;
    } catch(const std::exception& ex) {
        cerr << "general error! " << ex.what() << endl;
    }
}
