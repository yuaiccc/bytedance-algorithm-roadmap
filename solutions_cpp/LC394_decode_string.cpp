/**
 * LeetCode 394 - Decode String
 * https://leetcode.com/problems/decode-string/
 * Difficulty: Medium
 *
 * Problem:
 * Given an encoded string, return its decoded string. The encoding rule is:
 * k[encoded_string], where the encoded_string inside the square brackets is
 * repeated exactly k times. k is guaranteed to be a positive integer. The input
 * string is always valid; no extra spaces; brackets are well-formed.
 *
 * Approach:
 * Iterate through the string. Accumulate digits into a repeat count, and
 * accumulate letters into the current string. On '[' push (current string,
 * current count) onto a stack and reset both. On ']' pop the previous string
 * and count, then append currentString repeated count times to the previous
 * string. This naturally handles nesting like "3[a2[c]]" -> "accaccacc".
 *
 * Complexity:
 * - Time: O(N) where N is the length of the *decoded* output (each output char
 *   is constructed once). If measured against the encoded length, the work is
 *   proportional to the output size.
 * - Space: O(N) for the output and the stack.
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    string decodeString(string s) {
        stack<pair<string, int>> st; // (previous string, repeat count)
        string cur;
        int num = 0;

        for (char ch : s) {
            if (isdigit(ch)) {
                num = num * 10 + (ch - '0');
            } else if (ch == '[') {
                // Save context, start a new group.
                st.push({cur, num});
                cur.clear();
                num = 0;
            } else if (ch == ']') {
                // Pop and repeat.
                auto [prev, rep] = st.top();
                st.pop();
                for (int i = 0; i < rep; ++i) {
                    prev += cur;
                }
                cur = move(prev);
            } else {
                // A letter.
                cur += ch;
            }
        }
        return cur;
    }
};

// Optional: quick test
// int main() {
//     Solution s;
//     cout << s.decodeString("3[a2[c]]") << endl;    // accaccacc
//     cout << s.decodeString("2[abc]3[cd]ef") << endl; // abcabccdcdcdef
//     return 0;
// }
