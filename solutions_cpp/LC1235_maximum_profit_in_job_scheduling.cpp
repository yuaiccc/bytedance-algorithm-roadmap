/**
 * LeetCode 1235 - Maximum Profit in Job Scheduling
 * https://leetcode.com/problems/maximum-profit-in-job-scheduling/
 * Difficulty: Hard
 *
 * Problem:
 * You have n jobs, each with a start time, end time, and profit. A job
 * [startTime, endTime, profit] can be scheduled if it does not overlap with
 * another selected job (you may start a job exactly when another ends).
 * Return the maximum profit achievable by selecting a non-overlapping set.
 *
 * Approach:
 * DP + binary search. Sort jobs by end time. Let dp[i] = max profit using
 * the first i jobs (sorted). For the i-th job we either skip it (dp[i-1])
 * or take it: profit = job.profit + dp[k], where k is the number of jobs
 * whose end time <= this job's start time (i.e. the latest non-conflicting
 * prefix). Find k with binary search (upper_bound on the sorted end times).
 *
 * Complexity:
 * - Time: O(n log n)  — sorting + n binary searches.
 * - Space: O(n)
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int jobScheduling(vector<int>& startTime, vector<int>& endTime, vector<int>& profit) {
        int n = startTime.size();
        vector<tuple<int, int, int>> jobs;  // (end, start, profit)
        for (int i = 0; i < n; i++) {
            jobs.push_back({endTime[i], startTime[i], profit[i]});
        }
        sort(jobs.begin(), jobs.end());  // by end time

        vector<int> endTimes(n);
        for (int i = 0; i < n; i++) endTimes[i] = get<0>(jobs[i]);

        vector<long long> dp(n + 1, 0);  // dp[i] = best profit using first i jobs
        for (int i = 1; i <= n; i++) {
            auto [e, s, p] = jobs[i - 1];
            // largest prefix of jobs with end time <= start time s
            int k = upper_bound(endTimes.begin(), endTimes.end(), s) - endTimes.begin();
            long long take = p + dp[k];
            long long skip = dp[i - 1];
            dp[i] = max(take, skip);
        }
        return (int)dp[n];
    }
};

// Optional: main with test cases
int main() {
    Solution sol;
    vector<int> st = {1, 2, 3, 3};
    vector<int> et = {3, 4, 5, 6};
    vector<int> pf = {50, 10, 40, 70};
    cout << sol.jobScheduling(st, et, pf) << endl;  // Expected: 120

    vector<int> st2 = {1, 2, 3, 4, 6};
    vector<int> et2 = {3, 5, 10, 6, 9};
    vector<int> pf2 = {20, 20, 100, 70, 60};
    cout << sol.jobScheduling(st2, et2, pf2) << endl;  // Expected: 150
    return 0;
}
