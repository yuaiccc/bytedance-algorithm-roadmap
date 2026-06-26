/**
 * LeetCode 43 - Multiply Strings
 * https://leetcode.com/problems/multiply-strings/
 * Difficulty: Medium
 *
 * Problem:
 * Given two non-negative integers represented as strings num1 and num2,
 * return their product as a string without using built-in big-integer
 * conversion.
 *
 * Approach:
 * Grade-school multiplication. The product of two numbers of lengths n1
 * and n2 has at most n1 + n2 digits, so allocate a result array of that
 * size. For each pair of digits (i from num1, j from num2) placed at
 * positions (i+j, i+j+1), multiply them and add into the result, carrying
 * the high part into position i+j. Finally skip leading zeros and build the
 * string.
 *
 * Complexity:
 * - Time: O(n1 * n2)
 * - Space: O(n1 + n2)
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string multiply(string num1, string num2) {
        int n1 = num1.size(), n2 = num2.size();
        vector<int> res(n1 + n2, 0);

        for (int i = n1 - 1; i >= 0; i--) {
            for (int j = n2 - 1; j >= 0; j--) {
                int mul = (num1[i] - '0') * (num2[j] - '0');
                int p1 = i + j;      // carry position
                int p2 = i + j + 1;  // units position
                int sum = mul + res[p2];
                res[p2] = sum % 10;
                res[p1] += sum / 10;  // may build up; handled next iteration
            }
        }

        string ans;
        for (int x : res) {
            if (!(ans.empty() && x == 0)) ans.push_back(x + '0');  // skip leading zeros
        }
        return ans.empty() ? "0" : ans;
    }
};

// Optional: main with test cases
int main() {
    Solution sol;
    cout << sol.multiply("2", "3") << endl;        // 6
    cout << sol.multiply("123", "456") << endl;    // 56088
    cout << sol.multiply("0", "0") << endl;        // 0
    return 0;
}
