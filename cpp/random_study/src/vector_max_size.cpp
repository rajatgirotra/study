#include <iostream>
#include <vector>
using namespace std;

struct MyType {
    double d[1000];
};

// 230584300921369395
// 2305843009213693

int main() {
    vector<MyType> v;
    cout << v.max_size();
}