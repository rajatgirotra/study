#include <iostream>
#include <algorithm>
#include <fstream>
#include <boost/program_options.hpp>
#include <thread>
#include <memory>
using namespace std;
namespace po = boost::program_options;

namespace
{
    //Reverse a string in place.
    //Will only reverse charCount characters
    //Is re-entrant
    void reverse_func(string::iterator start, string::iterator end, size_t charCount)
    {
        while(charCount > 0)
        { 
            string::iterator::value_type tmp(*start);
            *start++ = *(--end);
            *end = tmp;
            charCount -= 2;
        }
    }

    void process(string& inputText, const size_t& parallel_threads)
    {
        cout << "Input text size: " << inputText.size() << endl;
        //Calculate how many chars each thread will need to reverse.
        //All threads will be given (almost) equal load.
        size_t q = inputText.size() / parallel_threads;
        size_t r = inputText.size() % parallel_threads;
        if(q%2 != 0)
        {
            --q;
            r+=parallel_threads;
        }
        size_t charsPerThread[parallel_threads];
        std::fill(charsPerThread, charsPerThread + parallel_threads, q);
        int index = 0;
        while(r > 1)
        {
            charsPerThread[index++] += 2;
            r -= 2;
        }

        //Create threads now. Each thread will reverse a portion/block of the string.
        std::thread* threadArr[parallel_threads];
        string::iterator start = inputText.begin();
        string::iterator end = inputText.end();
        for(size_t i = 0; i < parallel_threads; ++i)
        {
            threadArr[i] = new std::thread(&reverse_func, start, end, charsPerThread[i]);
            cout << "Thread " << threadArr[i]->get_id() << " reversing " << charsPerThread[i] << " characters\n";
            start += charsPerThread[i]/2;
            end -= charsPerThread[i]/2;
        }
        for(size_t i = 0; i < parallel_threads; ++i) { threadArr[i]->join(); }
        for(size_t i = 0; i < parallel_threads; ++i) { delete threadArr[i]; }
    }

    //Uses boost program_options.
    class Options
    {
        private:
            po::variables_map m_vm;
            po::options_description m_desc;

        public:
            Options() : m_desc("Allowed Options")
            {
                m_desc.add_options()
                    // option to print the help message
                    ("help,h", "Print this help message")
                    // option to get the string from file
                    ("file,f", po::value<string>()->default_value("inputFile.txt"), "filename containing text to be reversed")
                    // option to get the number of threads to use to reverse the string. Default is 1 thread.
                    ("parallelDegree,p", po::value<size_t>()->default_value(1), "Maximum number of blocks into which the text may be divided for reversing");
            }

            //Process in the command line parameters argc and argv
            void process(int argc, char* argv[])
            {
                po::store(po::parse_command_line(argc, argv, m_desc), m_vm);
                po::notify(m_vm);
                if(m_vm.count("help"))
                {
                    usage();
                    exit(-1);
                }
            }

            //Function to get an option, converted to the correct type.
            template <typename T>
            T get(const char* optionName)
            {
                T value = m_vm[optionName].template as<T>();
                return value;
            }

            void usage() { cout << m_desc << endl; }

    } _options;
}

int main(int argc, char* argv[])
{
    //Process options first
    _options.process(argc,argv);

    //Read the input text into a string
    std::stringstream buffer; //buffer to hold the input sequence of characters
    ifstream iFile(_options.get<string>("file").c_str());
    if(!iFile)
    {
        cerr << "Unable to open file: " << _options.get<string>("file") << " for reading" << endl;
        return -1;
    }
    buffer << iFile.rdbuf();
    string inputText = buffer.str();
    inputText.pop_back();//remove the end of line character from the buffer.
    buffer.str(""); //clear buffer now.

    //How many threads do we need to run parallely??
    size_t parallel_threads = _options.get<size_t>("parallelDegree");

    //Reverse a string using multiple threads for better performance.
    process(inputText, parallel_threads);

    ofstream outFile("outFile.txt");
    outFile << inputText;
    outFile.close();
    iFile.close();
    return 0;
}
