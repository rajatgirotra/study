#include <iostream>
#include <chrono>
#include <vector>
#include <thread>
#include <iterator>
using namespace std;

int main()
{
    vector<string> vec;
    vec.push_back("Rajat");
    vec.push_back("ABC");
    vec.push_back("ERF");
    vec.push_back("QWE");
    vec.push_back("HJK");

    std::this_thread::sleep_for(std::chrono::seconds(1));

    std::copy(vec.cbegin(), vec.cend(), std::ostream_iterator<string>(cout, "\n"));

    return 0;
}



