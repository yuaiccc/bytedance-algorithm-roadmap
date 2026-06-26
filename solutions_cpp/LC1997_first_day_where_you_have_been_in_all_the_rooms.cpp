/**
 * LeetCode 1997 - First Day Where You Have Been in All the Rooms
 * https://leetcode.com/problems/first-day-where-you-have-been-in-all-the-rooms/
 * Difficulty: Hard
 *
 * Problem:
 * There are n rooms numbered 0..n-1 and an array nextVisit. You start in
 * room 0 on day 0. When you visit a room for the i-th time:
 *   - if i is odd (first visit), the next day you visit nextVisit[room];
 *   - if i is even (second+ visit), the next day you visit (room+1) % n.
 * Return the label of the first day on which you have visited every room,
 * modulo 1e9 + 7. It is guaranteed 0 <= nextVisit[i] <= i.
 *
 * Approach:
 * Let g[i] = the day on which room i is visited for the FIRST time (g[0]=0).
 * To first visit room i+1 you must: first visit room i (day g[i]); go to
 * nextVisit[i] the next day (1 day); re-traverse from nextVisit[i] back to
 * room i, which takes (g[i] - g[nextVisit[i]]) days (the same span as the
 * original first-visit of nextVisit[i] to first-visit of i); then advance
 * to room i+1 the following day (1 day). Hence:
 *     g[i+1] = 2*g[i] - g[nextVisit[i]] + 2   (mod M).
 * The answer is g[n-1] (the day room n-1 is first reached, when all rooms
 * have been visited). Modular arithmetic is used throughout with +M to keep
 * the subtraction non-negative.
 *
 * Complexity:
 * - Time: O(n)
 * - Space: O(n)
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int firstDayBeenInAllRooms(vector<int>& nextVisit) {
        const long long M = 1e9 + 7;
        int n = nextVisit.size();
        vector<long long> g(n, 0);  // g[i] = first day room i is visited
        g[0] = 0;
        for (int i = 1; i < n; i++) {
            // g[i] = 2*g[i-1] - g[nextVisit[i-1]] + 2
            g[i] = (2 * g[i - 1] - g[nextVisit[i - 1]] + 2 + M) % M;
        }
        return (int)g[n - 1];
    }
};

// Optional: main with test cases
int main() {
    Solution sol;
    vector<int> a = {0, 0};
    cout << sol.firstDayBeenInAllRooms(a) << endl;  // Expected: 2

    vector<int> b = {0, 0, 1, 0, 2};
    cout << sol.firstDayBeenInAllRooms(b) << endl;  // Expected: 26
    return 0;
}
