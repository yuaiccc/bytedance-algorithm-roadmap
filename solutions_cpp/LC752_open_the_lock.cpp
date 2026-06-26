/**
 * LeetCode 752 - Open the Lock
 * https://leetcode.com/problems/open-the-lock/
 * Difficulty: Medium
 *
 * Problem:
 * You have a lock with 4 circular wheels, each showing digits '0'-'9'. The
 * wheels can turn forward or backward by one step. The lock starts at "0000".
 * Given a list of deadends and a target combination, return the minimum number
 * of turns to reach the target, or -1 if impossible. A deadend cannot be
 * visited.
 *
 * Approach:
 * BFS over the state space of 4-digit strings ("0000".."9999", 10000 states).
 * From each state there are 8 neighbors (each of 4 wheels +/-1, wrapping with
 * mod 10). Use a hash set for deadends and a visited set. If "0000" is a
 * deadend return -1 immediately. BFS guarantees the shortest path.
 *
 * Complexity:
 * - Time: O(10000 * 8 * 4) = O(1) effectively (state space is constant).
 * - Space: O(10000) for the visited set.
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int openLock(vector<string>& deadends, string target) {
        unordered_set<string> dead(deadends.begin(), deadends.end());

        // If the start itself is a deadend, we can never move.
        if (dead.count("0000")) return -1;
        if (target == "0000") return 0;

        queue<string> q;
        unordered_set<string> visited;
        q.push("0000");
        visited.insert("0000");

        int turns = 0;
        while (!q.empty()) {
            int levelSize = (int)q.size();
            ++turns;
            while (levelSize--) {
                string cur = q.front();
                q.pop();
                // Try turning each of the 4 wheels up or down.
                for (int i = 0; i < 4; ++i) {
                    for (int delta : {1, -1}) {
                        string next = cur;
                        // Wrap 0/9 using mod 10 arithmetic.
                        next[i] = ((cur[i] - '0' + delta + 10) % 10) + '0';
                        if (visited.count(next) || dead.count(next)) continue;
                        if (next == target) return turns;
                        visited.insert(next);
                        q.push(next);
                    }
                }
            }
        }
        return -1; // target unreachable
    }
};

// ---- Local test harness ----
int main() {
    Solution sol;
    vector<string> d1 = {"0201", "0101", "0102", "1212", "2002"};
    cout << sol.openLock(d1, "0202") << endl; // 6

    vector<string> d2 = {"8888"};
    cout << sol.openLock(d2, "0009") << endl; // 1

    vector<string> d3 = {"8887", "8889", "8878", "8898",
                         "8788", "8988", "7888", "9888"};
    cout << sol.openLock(d3, "8888") << endl; // -1
    return 0;
}
