#include <iostream>
#include <string>
using namespace std;

//int countSetBits(size_t N) {
//    int res = 0;
//     while (N != 0) {
//         if(N & 0x01) {
//             ++res;
//         }
//         N >>= 1;
//     }
//     return res;
//}
//
//int countSetBitsOptimized(size_t N) {
//    int res = 0;
//    while( N != 0 ) {
//        N &= (N - 1);
//        ++res;
//    }
//    return res;
//}
//
int countSetBits(size_t N) {
    int count{};
    while(N != 0) {
        count += (N & 0x01);
        N >>= 1;
    }
    return count;
}

int countSetBitsOptimized(size_t N) {
    int count{};
    while (N != 0) {
        N &= (N-1);
        ++count;
    }
    return count;
}

int main() {
    for(int i : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9})  {
      cout << "countSetBits(" << i << "): " << countSetBits(i) << endl;
    }

    for(int i : {0, 1, 2, 3, 4, 5, 6, 7, 8, 9})  {
        cout << "countSetBitsOptimized(" << i << "): " << countSetBitsOptimized(i) << endl;
    }
}
