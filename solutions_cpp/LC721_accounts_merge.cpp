/**
 * LeetCode 721 - Accounts Merge
 * https://leetcode.com/problems/accounts-merge/
 * Difficulty: Medium
 *
 * Problem:
 * Given a list of accounts where each account is [name, email1, email2, ...],
 * merge accounts that share at least one common email. Return the merged
 * accounts with emails sorted lexicographically.
 *
 * Approach:
 * Union-Find (Disjoint Set Union) on emails.
 *   1) First pass: for every email, initialize its parent to itself and record
 *      its owner name.
 *   2) Second pass: within each account, union the first email with every other
 *      email (so all emails in the same account become connected).
 *   3) Group emails by their find() root.
 *   4) For each group, output [owner, sorted emails...].
 * Path compression + union keeps operations nearly O(1) (amortized O(alpha)).
 *
 * Complexity:
 * - Time: O(N * alpha(N) + N log N) where N is total number of emails.
 *         alpha is inverse Ackermann (~constant). The log factor is from
 *         sorting emails within each group.
 * - Space: O(N) for the DSU structures and grouping map.
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
    unordered_map<string, string> parent;
    unordered_map<string, string> owner;

    // Find with path compression.
    string find(const string& x) {
        if (parent[x] != x) parent[x] = find(parent[x]);
        return parent[x];
    }

    // Union two emails under the same root.
    void unite(const string& a, const string& b) {
        string ra = find(a);
        string rb = find(b);
        if (ra != rb) parent[rb] = ra;
    }

public:
    vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
        // Initialize each email's parent and owner.
        for (const auto& acc : accounts) {
            for (int i = 1; i < (int)acc.size(); ++i) {
                parent[acc[i]] = acc[i];
                owner[acc[i]] = acc[0];
            }
        }

        // Union all emails within the same account.
        for (const auto& acc : accounts) {
            string firstEmail = acc[1];
            for (int i = 2; i < (int)acc.size(); ++i) {
                unite(firstEmail, acc[i]);
            }
        }

        // Group emails by their root.
        unordered_map<string, set<string>> groups;
        for (const auto& [email, _] : parent) {
            groups[find(email)].insert(email);
        }

        // Build the result: [owner, sorted email, sorted email, ...].
        vector<vector<string>> merged;
        for (auto& [root, emails] : groups) {
            vector<string> account;
            account.push_back(owner[root]);
            for (const string& email : emails) account.push_back(email);
            merged.push_back(account);
        }
        return merged;
    }
};

// ---- Local test harness ----
void printAccounts(const vector<vector<string>>& accounts) {
    for (const auto& acc : accounts) {
        for (const string& s : acc) cout << s << " ";
        cout << endl;
    }
}

int main() {
    Solution sol;
    vector<vector<string>> accounts = {
        {"John", "johnsmith@mail.com", "john_newyork@mail.com"},
        {"John", "johnsmith@mail.com", "john00@mail.com"},
        {"Mary", "mary@mail.com"},
        {"John", "johnnybravo@mail.com"}
    };
    auto merged = sol.accountsMerge(accounts);
    printAccounts(merged);
    return 0;
}
