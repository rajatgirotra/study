#include <iostream>
#include <vector>
using namespace std;

int solution(std::vector<int>& A) {
    auto sum {0};
    auto prev_stacks {0};

    for(auto&& val : A) {
        val += prev_stacks;
        prev_stacks = val / 2;
        val %= 2;
        sum += val;
    }

    // do we have stacks left
    while(prev_stacks > 0) {
        sum += (prev_stacks % 2);
        prev_stacks /= 2;
    }
  
    return sum;
}

int main() {
   // std::vector<int> arr {4, 0, 3, 0};
    //std::vector<int> arr {1, 0, 4, 1};
   // std::vector<int> arr {2, 3};
   std::vector<int> arr {3, 1};
    cout << solution(arr) << endl;
    return 0;
}
