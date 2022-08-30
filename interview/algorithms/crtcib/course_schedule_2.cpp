/*
 There are a total of numCourses courses you have to take, labeled from 0 to numCourses - 1. You are given an array prerequisites where prerequisites[i] = [ai, bi] indicates that you must take course bi first if you want to take course ai.

For example, the pair [0, 1], indicates that to take course 0 you have to first take course 1.
Return the ordering of courses you should take to finish all courses. If there are many valid answers, return any of them. If it is impossible to finish all courses, return an empty array.

This problem is very similar to course_schedule_1. Just that here we need maintain an order of the courses.
*/

#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <iomanip>
using namespace std;


class Solution {
    public:
        bool dfs(int course,
                 std::unordered_map<int, std::vector<int>>& course_map,
                 std::vector<bool>& visited,
                 std::unordered_set<int>& cycle,
                 std::vector<int>& course_order) {
            // if this course is found in the cycle set, this means a cycle exists. return false.
            if (cycle.find(course) != cycle.end()) {
                return false;
            }

            // if this course is already visited, return true
            if(visited[course]) {
                return true;
            }

            //add this course to the cycle set
            cycle.emplace(course);

            // recursively iterate the pre-requisites of this course.
            for(auto&& pre_req : course_map[course]) {
                if(!dfs(pre_req, course_map, visited, cycle, course_order)) {
                    return false;
                }
            }

            // all ok
            cycle.erase(course);
            visited[course] = true;
            course_order.emplace_back(course);
            return true;
        }

        vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
            // create a hash map of course and its dependencies.
            std::unordered_map<int, std::vector<int>> course_map;
            std::vector<bool> visited(numCourses, false);
            std::unordered_set<int> cycle;
            std::vector<int> course_order;
            for(const auto& item : prerequisites) {
                course_map[item[0]].emplace_back(item[1]);
            }

            //iterate over each node in the graph and run dfs() on it.
            for(int course = 0; course < numCourses; ++course) {
                if (!dfs(course, course_map, visited, cycle, course_order)) {
                    return std::vector<int>{};
                }
            }
            return course_order;
        }
};

int main() {
    /*
    vector<vector<int>> prerequisites;
    prerequisites.emplace_back(std::vector<int>{1,0});
    prerequisites.emplace_back(std::vector<int>{0,1}); // numCourses = 2
    */

    /*
    vector<vector<int>> prerequisites;
    prerequisites.emplace_back(std::vector<int>{1,0}); //numCourses = 2
    */

    vector<vector<int>> prerequisites;
    prerequisites.emplace_back(std::vector<int>{1,0});
    prerequisites.emplace_back(std::vector<int>{2,0});
    prerequisites.emplace_back(std::vector<int>{3,1});
    prerequisites.emplace_back(std::vector<int>{3,2}); //numCourses = 4

    Solution sol;

    if(auto order = sol.findOrder(4, prerequisites); order.empty()) {
        cout << "No possible order";
    } else {
        for(auto&& o : order) {
           cout << o << "  ";
        }
    }
    cout << endl;
}
