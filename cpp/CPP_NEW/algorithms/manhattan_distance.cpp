#include <vector>
#include <unordered_map>
#include <iostream>
#include <cmath>
#include <set>
using namespace std;

struct Coord {
    int m_x{};
    int m_y{};

    Coord(int x, int y) : m_x(x), m_y(y) {}

    friend bool operator < (const Coord& lhs, const Coord& rhs) {
        return std::tie(lhs.m_x, lhs.m_y) < std::tie(rhs.m_x, rhs.m_y);
    }

    friend ostream& operator << (ostream& os, const Coord& rhs) {
        os << "(" << rhs.m_x << ", " << rhs.m_y << ") ";
        return os;
    }
};

int solution(int K, vector<vector<int>>& A) {
    // create a map of empty cells and houses
    //vector<vector<int>> cellMap (5, std::vector<int>(6, 0));
    std::unordered_map<int, std::vector<Coord>> cellMap{};
    for(auto i = 0U; i < A.size(); ++i) {
        for(auto j = 0U; j < A[0].size(); ++j) {
            auto& lst = cellMap[A[i][j]];
            lst.emplace_back(i, j);
        }
    }

    for(auto&& [k, v] : cellMap) {
        cout << (k == 0 ? "Empty Cells" : "House Cells") << endl;
        for(auto&& coord : v) {
            cout << coord << " ";
        }
        cout << endl;
    }

    //visit all empty spaces. For each empty space, check if all houses are K manhattan distance away.
    std::set<Coord> possibleCells{};
    auto&& emptyCells = cellMap[0];
    for(auto&& emptyCell : emptyCells) {
        bool found = true;
        for(auto&& houseCell : cellMap[1]) {
            if(abs(houseCell.m_x-emptyCell.m_x) + abs(houseCell.m_y-emptyCell.m_y) > K) {
                found = false;
                break;
            }
        }
        if(found) possibleCells.emplace(emptyCell.m_x, emptyCell.m_y);
    }
    return static_cast<int>(possibleCells.size());
}

int main() {
//    vector<vector<int>> A;
//    A.push_back(vector<int>{0, 1});
//    A.push_back(vector<int>{1, 0});
//    int K = 1;

//    vector<vector<int>> A;
//    A.push_back(vector<int>{0, 0, 0, 0});
//    A.push_back(vector<int>{0, 0, 1, 0});
//    A.push_back(vector<int>{1, 0, 0, 1});
//    int K = 2;

    vector<vector<int>> A;
    A.push_back(vector<int>{0, 0, 0, 1});
    A.push_back(vector<int>{0, 1, 0, 0});
    A.push_back(vector<int>{0, 0, 1, 0});
    A.push_back(vector<int>{1, 0, 0, 0});
    A.push_back(vector<int>{0, 0, 0, 0});
    int K = 4;


    auto ans = solution(K, A);
    cout << "Number of available empty store locations: " << ans << endl;
}