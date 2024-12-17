/*
 * https://www.youtube.com/watch?v=QoAuE1v2vxA&t=1209s
 * https://leetcode.com/problems/maximum-earnings-from-taxi/
There are n points on a road you are driving your taxi on. The n points on the road are labeled from 1 to n in the direction you are going, and you want to drive from point 1 to point n to make money by picking up passengers. You cannot change the direction of the taxi.
The passengers are represented by a 0-indexed 2D integer array rides, where rides[i] = [starti, endi, tipi] denotes the ith passenger requesting a ride from point starti to point endi who is willing to give a tipi dollar tip.
For each passenger i you pick up, you earn endi - starti + tipi dollars. You may only drive at most one passenger at a time.
Given n and rides, return the maximum number of dollars you can earn by picking up the passengers optimally.
Note: You may drop off a passenger and pick up a different passenger at the same point.

 Example 1:

Input: n = 5, rides = [[2,5,4],[1,5,1]]
Output: 7
Explanation: We can pick up passenger 0 to earn 5 - 2 + 4 = 7 dollars.
Example 2:

Input: n = 20, rides = [[1,6,1],[3,10,2],[10,12,3],[11,12,2],[12,15,2],[13,18,1]]
Output: 20
Explanation: We will pick up the following passengers:
- Drive passenger 1 from point 3 to point 10 for a profit of 10 - 3 + 2 = 9 dollars.
- Drive passenger 2 from point 10 to point 12 for a profit of 12 - 10 + 3 = 5 dollars.
- Drive passenger 5 from point 13 to point 18 for a profit of 18 - 13 + 1 = 6 dollars.
We earn 9 + 5 + 6 = 20 dollars in total.
*/
class Solution {
public:
    // long dp(int index, vector<int>& profit, const vector<vector<int>>& rides) {
    long long dp(const vector<vector<int>>& rides) {
        std::unordered_map<int, long long> maxProfits{};
        int last_index = rides.size() - 1;
        maxProfits[last_index] = rides[last_index][1] - rides[last_index][0] + rides[last_index][2];
        // cout << "dp(" << last_index << "): " << maxProfits[last_index] << endl;
        for(int i = rides.size() - 2; i >= 0; --i) {
            // you do not accept this ride.
            long long res1 = maxProfits[i+1];

            // you pick up this ride.
            long long res2 = rides[i][1] - rides[i][0] + rides[i][2];
            int j = i+1;
            while(j < rides.size()) {
                if (rides[j][0] >= rides[i][1]) {
                    res2 += maxProfits[j];
                    break;
                }
                ++j;
            }

            maxProfits[i] = std::max(res1, res2);
            // cout << "dp(" << i << "): " << maxProfits[i] << endl;
        }
        return maxProfits[0];
    }

    long long maxTaxiEarnings(int n, vector<vector<int>>& rides) {
        // sort the rides array by the 'start' point.
        std::sort(rides.begin(), rides.end(), [](const vector<int>& lhs, const vector<int>& rhs) {
            if(lhs[0] < rhs[0]) {
                return true;
            } else if (lhs[0] > rhs[0]) {
                return false;
            } else {
                return lhs[1] < rhs[1];
            }
        });

        // std::for_each(rides.begin(), rides.end(), [](auto& item) {
        //     cout << "[" << item[0] << ", " << item[1] << ", " << item[2] << "]\n";
        // });

        // std::unordered_map<int, long long> maxProfits{};
        return dp(rides);
    }
};