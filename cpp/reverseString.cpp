#include <iostream>
#include <iterator>
#include <algorithm>
#include <string>
#include <fstream>
#include <sstream>
#include <boost/thread/thread.hpp>
using namespace std;
using namespace boost;

void my_reverse(string::iterator start, string::iterator end, int chars)
{
#if 1
    while(chars > 0)
    {
        char tmp = *start;
        *start++ = *(--end);
        *end = tmp;
        chars -= 2;
    }
#endif
}

int main(int argc, char* argv[])
{

    int parallel_threads = 1;
    int chars = 0;
    if(argc > 3)
    {
       parallel_threads = atoi(argv[2]);
       chars = atoi(argv[3]);
    }

    string fileName(argv[1]);
    cout << "FileName: " << fileName <<"\nParallel threads: " << parallel_threads << endl;

    std::stringstream buffer;
    ifstream file(fileName.c_str());
    buffer << file.rdbuf();
    string str = buffer.str();
//    cout << str << endl;
    chars = str.size();

    /*int q = (str.size()%2==0 ? str.size()/parallel_threads : (str.size()-1)/parallel_threads);
    int r = str.size()%parallel_threads;*/
    int origChars = chars;
    int q = chars/parallel_threads;
    int r = chars%parallel_threads;
    if(q%2 != 0)
    {
        --q;
        r+=parallel_threads;
    }

    int charsToReverse[parallel_threads];
    std::fill(charsToReverse, charsToReverse+parallel_threads,q);
    int i = 0;
    while(r > 1)
    {
        charsToReverse[i++] += 2;
        r-=2;
    }

    std::copy(charsToReverse, charsToReverse+parallel_threads, std::ostream_iterator<int>(cout, "  "));
    cout << endl;

#if 1
    boost::thread* threadArr[parallel_threads];
    string::iterator start = str.begin();
    string::iterator end = str.end();
    for(int j = 0; j < parallel_threads; ++j)
    {

        threadArr[j] = new boost::thread(&my_reverse,
                                      start,
                                      end,
                                      charsToReverse[j]);
        start = start + charsToReverse[j]/2;
        end = end - charsToReverse[j]/2;
    }

    for(int j = 0; j < parallel_threads; ++j)
        threadArr[j]->join();

    ofstream out("file.txt");
    out << str;
    cout << str ;
    out.close();
    cout << endl;
#endif

 //   cout << str << endl;
    return 0;
}
