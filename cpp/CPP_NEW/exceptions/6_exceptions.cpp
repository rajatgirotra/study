#include <iostream>
#include <fstream>
#include <exception>
#include <string>
using namespace std;

void print_exception(const std::exception& e, size_t level = 0) {
    cerr << std::string(level, ' ') << "exception: " << e.what() << endl;
    try {
        std::rethrow_if_nested(e);
    } catch(const std::exception& ex) {
        print_exception(ex, ++level);
    } catch (...) {}
}

void open_file(const char* file_name) {
    try {
        std::fstream f(file_name);
        f.exceptions(std::ios_base::failbit);
    } catch(...) {
        std::throw_with_nested(std::runtime_error(string("failed to open file ").append(file_name)));
    }
}

void run() {
    try {
        open_file("nonexistant_file.txt");
    } catch(...) {
        std::throw_with_nested(std::runtime_error("run() failed.."));
    }
}
int main() {
    try {
        run();
    } catch(const std::exception& e) {
        print_exception(e);
    }
}
