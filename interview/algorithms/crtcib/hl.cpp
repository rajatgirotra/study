#include <iostream>
#include <fstream>
#include <sstream>
#include <cassert>
#include <string>
#include <cstring>
#include <unordered_map>
#include <iomanip>
using namespace std;

struct Result {
    uint32_t total_job_count{};
    uint32_t total_job_time{};
    bool is_union{true};
};

auto process(ifstream& ifs) {
    // read input line by line
    ifs.exceptions(std::ios_base::failbit);
    stringstream ss;
    ss.exceptions(std::ios_base::failbit);
    std::unordered_map<uint32_t, std::pair<uint32_t, bool>> jobs;
    string line{};
    Result res{};
    uint32_t sj;
    uint32_t time;
    uint32_t nj;
    char delimiter;
    while(ifs.good()) {
        try {
            getline(ifs, line);
            ss.str("");
            ss << line;
            ss >> sj; 
            ss >> delimiter;
            ss >> time; 
            ss >> delimiter;
            ss >> nj; 
            //cout << sj << " " << time << " " << nj << endl;
            ++res.total_job_count;
            res.total_job_time += time;
            jobs.emplace(std::piecewise_construct, std::forward_as_tuple(sj), std::forward_as_tuple(nj, false));
        } catch(...) {
            if(ifs.eof()) {
                cout << "Reached end of input\n";
                break; 
            } else if(ifs.fail() || ss.fail()) {
                cerr << "error trying to read input from file, possibly corrupted/invalid data in input file";
                exit(-1);
            } 
        }
    }

    auto iter = jobs.begin();
    while(iter != jobs.end()) {
        if(iter->second.second == true) {
            break;
        }
        iter->second.second = true;
        iter = jobs.find(iter->second.first);
    }

    for(auto&& [k, v] : jobs) {
        cout << k << " --> (" << v.first << ", " << std::boolalpha << v.second << ")" << endl;
        if(v.second == false) {
            res.is_union = false;
            break;
        }
    }
    return res;
}

int main(int argc, char** argv) {
    // get input csv file as argument
    if(argc < 2) {
        cerr << "Usage:\n\t" << argv[0] << "  <input_csv.txt>\n";
        return -1;
    }

    // validate input file can be opened for reading
    const char* const input_file = argv[1];
    ifstream ifs(input_file, std::ios_base::in);
    if(!ifs.good()) {
        cerr << "Failed to open file: " << input_file << " for reading\n";
        return -1;
    }

    // process file
    auto res = process(ifs);

    cout << "Total job count: " << res.total_job_count << endl;
    cout << "Total job time: " << res.total_job_time << endl;
    cout << "Average job time: " << (static_cast<double>(res.total_job_time))/res.total_job_count << endl;
    cout << "is union a linked list: " << std::boolalpha << res.is_union << endl;
}
