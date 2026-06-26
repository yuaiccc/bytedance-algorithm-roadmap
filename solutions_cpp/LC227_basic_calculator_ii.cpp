/**
 * LeetCode 227 - Basic Calculator II
 * https://leetcode.com/problems/basic-calculator-ii/
 * Difficulty: Medium
 *
 * Problem:
 * Given a string s which represents an expression, evaluate it and return its
 * value. The integer division should truncate toward zero. You may assume the
 * given expression is always valid. Operators are +, -, *, / and operands are
 * non-negative integers. No parentheses.
 *
 * Approach:
 * Parse the string left to right, accumulating the current number. Track the
 * last operator seen (initialized to '+'). When we hit an operator or the end
 * of the string, we act on the completed number based on the *previous*
 * operator:
 *   '+' or '-' -> push +num or -num onto a stack (defer addition/subtraction).
 *   '*' or '/' -> pop the top, multiply/divide by num, push result back.
 * The final answer is the sum of all values in the stack. This defers + and -
 * while eagerly evaluating * and / to respect precedence without parentheses.
 *
 * Complexity:
 * - Time: O(n)
 * - Space: O(n) for the stack.
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int calculate(string s) {
        stack<int> st;
        int num = 0;
        char op = '+'; // previous operator, default '+' for the first number
        int n = (int)s.size();

        for (int i = 0; i < n; ++i) {
            char ch = s[i];
            if (isdigit(ch)) {
                num = num * 10 + (ch - '0');
            }
            // When ch is an operator, or we are at the last character, process
            // the completed number using the previous operator.
            if ((!isdigit(ch) && ch != ' ') || i == n - 1) {
                switch (op) {
                    case '+': st.push(num); break;
                    case '-': st.push(-num); break;
                    case '*': st.top() *= num; break;
                    case '/': st.top() /= num; break; // truncates toward zero
                }
                op = ch;
                num = 0;
            }
        }

        int result = 0;
        while (!st.empty()) {
            result += st.top();
            st.pop();
        }
        return result;
    }
};

// Optional: quick test
// int main() {
//     Solution s;
//     cout << s.calculate("3+2*2") << endl;   // 7
//     cout << s.calculate(" 3/2 ") << endl;   // 1
//     cout << s.calculate(" 3+5 / 2 ") << endl; // 5
//     return 0;
// }
