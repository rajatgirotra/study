#include <iostream>
#include <array>
#include <vector>
#include <algorithm>
using namespace std;

template <size_t N>
auto assembly_line_chaining_dp(std::uint32_t e1, std::uint32_t e2, std::uint32_t x1, std::uint32_t x2,
                               std::array<std::uint32_t, N> al1, std::array<std::uint32_t, N>  al2,
                               std::array<std::uint32_t, N-1> t12, std::array<std::uint32_t, N-1> t21) {

    // create a resultant array to store the fastest times through every station on the two assembly lines.
    // res[i][j] is the time to move through station j on assembly line i
    std::array<std::array<std::uint32_t, N>, 2> res{};

    // create another array to store the optimum assembly line for each station
    std::array<std::uint32_t, N> stations{};

    // res[i][0] is trivial case
    res[0][0] = e1 + al1[0];
    res[1][0] = e2 + al2[0];
    stations[0] = res[0][0] < res[1][0] ? 0 : 1;

    for(auto station = 1; station < N; ++station) {
        res[0][station] = std::min(res[0][station-1] + al1[station], res[1][station-1] + t21[station-1] + al1[station]);
        res[1][station] = std::min(res[1][station-1] + al2[station], res[0][station-1] + t12[station-1] + al2[station]);
        stations[station] = (res[0][station] < res[1][station] ? 0 : 1);
    }

    auto minTime{0u};
    if(res[0][N-1] + x1 < res[1][N-1] + x2) {
        minTime = res[0][N-1] + x1;
        stations[N-1] = 0;
    } else {
        minTime = res[1][N-1] + x2;
        stations[N-1] = 1;
    }
    return minTime;
}

int main() {
    // cost to enter and exit assembly line 1 and 2
    std::uint32_t e1 = 2, e2 = 4, x1 = 3, x2 = 2;

    // times spent at each station on the two assembly lines
    std::array<std::uint32_t, 6> al1{7, 9, 3, 4, 8, 4};
    std::array<std::uint32_t, 6> al2{8, 5, 6, 4, 5, 7};

    // time to transfer between assembly lines
    std::array<std::uint32_t, al1.size()-1> t12{2, 3, 1, 3, 4};
    std::array<std::uint32_t, al1.size()-1> t21{2, 1, 2, 2, 1};

    auto res = assembly_line_chaining_dp(e1, e2, x1, x2, al1, al2, t12, t21);
    cout << "Minimum time through assembly line: " << res << endl;
}