#include <filesystem>
#include <iostream>
#include <string>
using namespace std;
namespace fs = std::filesystem;

void print_path_details(const fs::path& test_path) {
    cout << "Path: " << test_path << endl;

    if(test_path.has_root_name()) {
        cout << "Root Name: " << test_path.root_name() << endl;
    } else {
        cout << "no Root Name\n";
    }

    if(test_path.has_root_directory()) {
        cout << "Root Directory: " << test_path.root_directory() << endl;
    } else {
        cout << "no Root Directory\n";
    }

    if(test_path.has_root_path()) {
        cout << "Root Path: " << test_path.root_path() << endl;
    } else {
        cout << "no Root Path\n";
    }

    if(test_path.has_relative_path()) {
        cout << "Relative path: " << test_path.relative_path() << endl;
    } else {
        cout << "no Relative path\n";
    }

    if(test_path.has_parent_path()) {
        cout << "Parent path: " << test_path.parent_path() << endl;
    } else {
        cout << "no parent path\n";
    }

    if(test_path.has_filename()) {
        cout << "filename(): " << test_path.filename() << endl;
    } else {
        cout << "no filename\n";
    }

    if(test_path.has_stem()) {
        cout << "stem: " << test_path.stem() << endl;
    } else {
        cout << "no stem\n";
    }

    if(test_path.has_extension()) {
        cout << "extension: " << test_path.extension() << endl;
    } else {
        cout << "no extension\n";
    }

}

int main(int argc, char** argv) {
    fs::path test_path((argc >=2 ? fs::path(argv[1]) : fs::current_path()));
    print_path_details(test_path);

    // fs::path::begin()/end() allow you to iterate over path sections.
    cout << endl << endl;
    int i = 0;
    for(auto&& part : test_path) {
        cout << "Path part " << ++i << ": " << part << "\n";
    }

    // append paths using /= or append() function.
    fs::path p("/");
    p.append("home");
    p /= "study";
    cout << "appended path: " << p << endl;

    // concat paths using += or append() function.
    fs::path p2("/home/");
    p2.concat("rajat_");
    p2 += "girotra";
    cout << "concatenated path: " << p2 << endl;

}
