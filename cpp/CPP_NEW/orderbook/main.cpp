#include "PriceBucketManager.hpp"
#include <iostream>

using namespace std;
using namespace raj;

int main(int argc, char** argv) {
    PriceBucketManager<> pbm;
    pbm.addBucket(100000);
    pbm.addBucket(102000);
    pbm.addBucket(104000);
    pbm.addBucket(106000);

    auto start_it = pbm.begin<::raj::Side::SELL>();
    auto end_it = pbm.end<::raj::Side::SELL>();

    while(start_it != end_it) {
        cout << *start_it << endl;
        ++start_it;
    }

}