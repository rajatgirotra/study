/*
 * Loading a file into a string.
 * before c++17, to find the size of a file, you would position the file pointer to the end of the file and then read the
 * position again. with c++17 filesystem, we can use fs::file_size().
 */

#include <iostream>
#include <filesystem>
#include <string>
#include <fstream>
#include <limits>
using namespace std;
namespace fs = std::filesystem;

[[nodiscard]] string get_file_contents(const fs::path& filePath) {
    std::ifstream ifs{filePath, std::ios_base::in};

    if(!ifs.is_open()) {
        std::throw_with_nested(std::runtime_error("Cannot open " + filePath.string()));
    }

    const auto size = fs::file_size(filePath);
    if(size > std::numeric_limits<std::string::size_type>::max()) {
        std::throw_with_nested(std::runtime_error("file too large to fit in size_t! " + filePath.string()));
    }

    string str(static_cast<std::string::size_type>(size), 0);

    ifs.read(str.data(), static_cast<std::streamsize>(str.size()));

    if(!ifs) {
        std::throw_with_nested(std::runtime_error("could not read full file contents from file " + filePath.string()));
    }
    return str;
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv) {
    fs::path filePath {"/home/rajatgirotra/study/cpp/CPP_NEW/filesystem/filesystem_5.cpp"};
    cout << get_file_contents(filePath) << endl;
}
