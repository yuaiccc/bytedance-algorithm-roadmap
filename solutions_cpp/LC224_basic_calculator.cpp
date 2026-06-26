/**
 * LeetCode 224 - Basic Calculator
 * https://leetcode.com/problems/basic-calculator/
 * Difficulty: Hard
 *
 * Problem:
 * Given a string s representing a valid expression, implement a basic
 * calculator to evaluate it and return the result. The expression may contain
 * open '(' and closing ')', the plus '+' or minus '-' operator, non-negative
 * integers and empty spaces ' '. No multiplication or division.
 *
 * Approach:
 * Scan left to right maintaining a running `result` and a `sign` (+1 or -1).
 * Accumulate digits into a number. On '+'/'-', add sign*num to the result and
 * flip sign accordingly. On '(', push the current result and sign onto a stack,
 * then reset result=0 and sign=+1 to evaluate the sub-expression. On ')', add
 * the last number, then pop the saved result and sign to combine: the value
 * inside the parentheses is merged with the context that was deferred.
 *
 * Complexity:
 * - Time: O(n)
 * - Space: O(n) for the stack in the worst case of deep nesting.
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int calculate(string s) {
        stack<int> st;        // stores (previous result, sign before '(')
        int result = 0;
        int sign = 1;         // 1 for '+', -1 for '-'
        int num = 0;
        int n = (int)s.size();

        for (int i = 0; i < n; ++i) {
            char ch = s[i];
            if (isdigit(ch)) {
                num = num * 10 + (ch - '0');
            } else if (ch == '+') {
                result += sign * num;
                num = 0;
                sign = 1;
            } else if (ch == '-') {
                result += sign * num;
                num = 0;
                sign = -1;
            } else if (ch == '(') {
                // Save the outer context, evaluate the inner expression fresh.
                st.push(result);
                st.push(sign);
                result = 0;
                sign = 1;
            } else if (ch == ')') {
                // Finalize the inner expression.
                result += sign * num;
                num = 0;
                // Combine with the outer context.
                int outerSign = st.top(); st.pop();
                int outerResult = st.top(); st.pop();
                result = outerResult + outerSign * result;
            }
            // spaces are ignored.
        }
        // Add the last accumulated number.
        result += sign * num;
        return result;
    }
};

// Optional: quick test
// int main() {
//     Solution s;
//     cout << s.calculate("1 + 1") << endl;          // 2
//     cout << s.calculate(" 2-1 + 2 ") << endl;      // 3
//     cout << s.calculate("(1+(4+5+2)-3)+(6+8)") << endl; // 23
//     return 0;
// }
