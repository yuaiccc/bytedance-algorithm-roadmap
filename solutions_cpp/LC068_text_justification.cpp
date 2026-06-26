/**
 * LeetCode 68 - Text Justification
 * https://leetcode.com/problems/text-justification/
 * Difficulty: Hard
 *
 * Problem:
 * Given an array of words and a max width, format the text such that each
 * line has exactly maxWidth characters and is fully (left and right)
 * justified. Pack as many words as possible per line greedily. Distribute
 * extra spaces as evenly as possible between words, with the larger spaces
 * on the left. The last line (and any line with a single word) is
 * left-justified with no extra spaces between words.
 *
 * Approach:
 * Greedily pack words into a line while (running length + 1 + next word) <=
 * maxWidth (the +1 accounts for the mandatory single space between words).
 * Once a line's word range [i, j) is decided:
 *   - Last line or single word: left-justify, pad the trailing spaces.
 *   - Otherwise: totalSpaces = maxWidth - sum(word lengths); distribute
 *     across (count-1) gaps; the first (extra) gaps get one extra space.
 * Advance i = j and repeat.
 *
 * Complexity:
 * - Time: O(N) where N is total characters (each word processed once).
 * - Space: O(maxWidth) per line / O(N) for output.
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<string> fullJustify(vector<string>& words, int maxWidth) {
        vector<string> res;
        int n = words.size();
        int i = 0;
        while (i < n) {
            // Greedily determine word range [i, j) for this line.
            int lineLen = (int)words[i].size();
            int j = i + 1;
            while (j < n && lineLen + 1 + (int)words[j].size() <= maxWidth) {
                lineLen += 1 + (int)words[j].size();
                j++;
            }

            int count = j - i;  // number of words on this line
            string line;
            if (j == n || count == 1) {
                // Last line or single word: left-justified.
                for (int k = i; k < j; k++) {
                    line += words[k];
                    if (k != j - 1) line += " ";
                }
                while ((int)line.size() < maxWidth) line += " ";
            } else {
                int totalChars = 0;
                for (int k = i; k < j; k++) totalChars += (int)words[k].size();
                int totalSpaces = maxWidth - totalChars;
                int gaps = count - 1;
                int spacePer = totalSpaces / gaps;
                int extra = totalSpaces % gaps;  // leftmost `extra` gaps get +1
                for (int k = i; k < j; k++) {
                    line += words[k];
                    if (k != j - 1) {
                        int sp = spacePer + ((k - i) < extra ? 1 : 0);
                        line += string(sp, ' ');
                    }
                }
            }
            res.push_back(line);
            i = j;
        }
        return res;
    }
};

// Optional: main with test cases
int main() {
    Solution sol;
    vector<string> words = {"This", "is", "an", "example", "of", "text", "justification."};
    auto res = sol.fullJustify(words, 16);
    for (auto& line : res) cout << "[" << line << "]" << endl;
    return 0;
}
