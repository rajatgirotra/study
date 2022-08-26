#include <iostream>
#include <fstream>
#include <sstream>
#include <cassert>
#include <string>
#include <cstring>
#include <unordered_map>
#include <iomanip>
#include <limits>
#include <map>
using namespace std;

struct job_detail {
    uint32_t job_time{};
    int32_t next_job{};
    bool visited{};

    job_detail(uint32_t t, int32_t j, bool arg) : job_time(t), next_job(j), visited(arg) {}


    friend ostream& operator << (ostream& os, const job_detail& rhs) {
       os << "job_time: " << rhs.job_time << ", next_job: " << rhs.next_job << ", visited: " << std::boolalpha << rhs.visited;
       return os;
    }
};

struct job_chain {
    uint32_t total_job_count{};
    uint32_t total_job_time{};
    int start_job{};
    int end_job{};
};

job_chain build_chain(auto iter, auto& jobs) {
    job_chain c;
    c.start_job = iter->first;
    while(true) { 
        iter->second.visited = true;
        ++c.total_job_count;
        c.total_job_time += iter->second.job_time;
        if (iter->second.next_job != 0) {
            c.end_job = iter->second.next_job;
        }

        if (iter->second.next_job == 0)
            break; 
        iter = jobs.find(iter->second.next_job);
        if(iter == jobs.end()) {
            cout << "Malformed Input A\n";
            exit(-1);
        }
    } 
    return c;
}

void process(ifstream& ifs) {
    // read input line by line
    stringstream ss;
    ifs.exceptions(std::ios_base::failbit);
    ss.exceptions(std::ios_base::failbit);
    std::map<int32_t, job_detail> jobs;
    string line{};
    int32_t sj{}, nj{}; 
    uint32_t time{};
    char delimiter{};
  
    //skip header
    ifs.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    while(ifs.good()) {
        try {
            getline(ifs, line);
            ss.str("");
            ss << line;
            ss >> sj >> delimiter >> time >> delimiter >> nj; 
            ss.clear();
            jobs.emplace(std::piecewise_construct, std::forward_as_tuple(sj), std::forward_as_tuple(time, nj, false));
        } catch(...) {
            if(ifs.eof()) {
                cout << "Reached end of input\n";
                break; 
            } else if(ifs.fail() || ss.fail()) {
                cout << "Malformed Input\n";
                exit(-1);
            } 
        }
    }

    std::multimap<uint32_t, job_chain, std::greater<uint32_t>> chains;
    int start_job = -1;
    int end_job = -1;

    for(auto iter = jobs.begin(); iter != jobs.end(); ++iter) {
        // have we visited this log before
        if(iter->second.visited) {
            continue;
        }
        auto chain = build_chain(iter, jobs);
        chains.emplace(chain.total_job_time, chain);
    }

    for(auto&& [k, v] : chains) {
        cout << "-\n";
        cout << "start_job: " << v.start_job << endl;
        cout << "last_job: " << v.end_job << endl;
        cout << "number_of_jobs: " << v.total_job_count << endl;
        uint32_t hrs{}, mins{}, secs{v.total_job_time};
        mins = secs / 60; secs %= 60; hrs = mins / 60; mins %= 60;
        cout << setfill('0');
        cout << "job_chain_runtime: " << setw(2) << hrs << ":" << setw(2) << mins << ":" << setw(2) << secs << endl;
        secs = v.total_job_time/v.total_job_count;
        mins = secs / 60; secs %= 60; hrs = mins / 60; mins %= 60;
        cout << "average_job_time: " << setw(2) << hrs << ":" << setw(2) << mins << ":" << setw(2) << secs << endl;
        //cout << "job_chain_runtime: " << v.total_job_time << endl;
        //cout << "average_job_time: " << v.total_job_time/v.total_job_count << endl;
    } 

    return;
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
    process(ifs);

    //cout << "Total job count: " << res.total_job_count << endl;
    //cout << "Total job time: " << res.total_job_time << endl;
    //cout << "Average job time: " << (static_cast<double>(res.total_job_time))/res.total_job_count << endl;
    //cout << "is union a linked list: " << std::boolalpha << res.is_union << endl;
}
