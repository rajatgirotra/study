/*
There are a total of numCourses courses you have to take, labeled from 0 to numCourses - 1. You are given an array prerequisites where prerequisites[i] = [ai, bi] indicates that you must take course bi first if you want to take course ai.

For example, the pair [0, 1], indicates that to take course 0 you have to first take course 1.
Return true if you can finish all courses. Otherwise, return false.
*/

#include <iostream>
#include <unordered_map>
#include <vector>
#include <iomanip>
using namespace std;


class Solution {
    public:
        bool canFinishHelper(int course,  std::unordered_map<int, std::vector<int>>& course_map, std::vector<bool>& visited) {
            if (visited[course]) {
                return false;
            }

           if (course_map[course].empty()) {
               return true;
           }

           visited[course] = true;
           for(const auto& pre : course_map[course]) {
               if(!canFinishHelper(pre, course_map, visited)) {
                   return false;
               }
           }
           visited[course] = false;
           course_map[course].clear();
           return true;
        }

        bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
 
            // create a hash map of course and its dependencies.
            std::unordered_map<int, std::vector<int>> course_map;
            std::vector<bool> visited(numCourses, false);
            for(const auto& item : prerequisites) {
                course_map[item[0]].emplace_back(item[1]);
            }

            // for each course, check if you can finish it
            for(auto& iter : course_map) {
                if(!canFinishHelper(iter.first, course_map, visited))
                    return false;
            }
            return true;
        }
};

int main() {
    vector<vector<int>> prerequisites;
    prerequisites.emplace_back(std::vector<int>{1,0});
    prerequisites.emplace_back(std::vector<int>{0,1});

    cout << boolalpha << canFinish(2, prerequisites);
}
