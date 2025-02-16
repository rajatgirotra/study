#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
  std::set<int> s1 {2, 5};

  auto iter = std::lower_bound(s1.begin(), s1.end(), 4);
  if(iter == s1.end()) {
    cout << "Not found\n";
  } else {
    cout << "Found elem: " << *iter << endl;
  }
  }