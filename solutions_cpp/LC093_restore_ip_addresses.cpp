/**
 * LeetCode 93 - Restore IP Addresses
 * https://leetcode.com/problems/restore-ip-addresses/
 * Difficulty: Medium
 *
 * Problem:
 * Given a string of digits, return all possible valid IPv4 addresses that
 * can be formed by inserting three dots. A segment must be 1-3 digits, have
 * no leading zero unless it is exactly "0", and be between 0 and 255.
 *
 * Approach:
 * Backtracking over the 4 segments. At each step try a segment of length
 * 1, 2, or 3 starting at the current index; validate it (no leading zero,
 * value <= 255); append it and recurse. When 4 segments are collected,
 * accept only if the entire string is consumed. The branching factor is at
 * most 3 with depth 4, so the search space is tiny (bounded by 3^4).
 *
 * Complexity:
 * - Time: O(1) (bounded by 3^4 = 81 candidate splits, each O(n) to build).
 * - Space: O(1) excluding output.
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<string> restoreIpAddresses(string s) {
        vector<string> res;
        vector<string> cur;
        backtrack(s, 0, cur, res);
        return res;
    }

private:
    void backtrack(const string& s, int idx,
                   vector<string>& cur, vector<string>& res) {
        if (cur.size() == 4) {
            if (idx == (int)s.size()) {
                res.push_back(cur[0] + "." + cur[1] + "." + cur[2] + "." + cur[3]);
            }
            return;
        }
        // Pruning: remaining length must fit in (4 - size) .. 3*(4 - size).
        int remaining = (int)s.size() - idx;
        int need = 4 - (int)cur.size();
        if (remaining < need || remaining > 3 * need) return;

        for (int len = 1; len <= 3; len++) {
            if (idx + len > (int)s.size()) break;
            string seg = s.substr(idx, len);
            if (!valid(seg)) continue;
            cur.push_back(seg);
            backtrack(s, idx + len, cur, res);
            cur.pop_back();
        }
    }

    bool valid(const string& seg) {
        if (seg.size() > 1 && seg[0] == '0') return false;  // leading zero
        int val = stoi(seg);
        return val >= 0 && val <= 255;
    }
};

// Optional: main with test cases
int main() {
    Solution sol;
    auto r1 = sol.restoreIpAddresses("25525511135");
    for (auto& ip : r1) cout << ip << endl;  // ["255.255.11.135","255.255.111.35"]

    auto r2 = sol.restoreIpAddresses("0000");
    for (auto& ip : r2) cout << ip << endl;  // ["0.0.0.0"]
    return 0;
}
