/**
 * LeetCode 127 - Word Ladder
 * https://leetcode.com/problems/word-ladder/
 * Difficulty: Hard
 *
 * Problem:
 * Given two words beginWord and endWord, and a dictionary wordList, return the
 * number of words in the shortest transformation sequence from beginWord to
 * endWord where each step changes exactly one letter and the intermediate word
 * must exist in wordList. Return 0 if no such sequence exists.
 *
 * Approach:
 * Bidirectional BFS. Start one BFS from beginWord and one from endWord,
 * expanding the smaller frontier each iteration to minimize work. To generate
 * neighbors, for each position try all 26 letters (pattern-based neighbor
 * generation): O(26 * L) per word rather than scanning the whole list. When a
 * word from one frontier is found in the other frontier, the two halves meet
 * and the total ladder length is currentSteps + 1. Remove used words from the
 * dictionary to mark them visited.
 *
 * Complexity:
 * - Time: O(N * L * 26) where N = wordList size, L = word length. (Pattern-
 *   based neighbor generation avoids the O(N^2 * L) pairwise comparison.)
 * - Space: O(N) for the dictionary set and BFS frontiers.
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> dict(wordList.begin(), wordList.end());
        if (!dict.count(endWord)) return 0; // endWord must be reachable

        unordered_set<string> beginSet{beginWord};
        unordered_set<string> endSet{endWord};
        int ladder = 1; // counts beginWord as the first step

        while (!beginSet.empty() && !endSet.empty()) {
            // Always expand the smaller frontier for efficiency.
            if (beginSet.size() > endSet.size()) {
                swap(beginSet, endSet);
            }

            unordered_set<string> nextLevel;
            for (string word : beginSet) {
                for (int i = 0; i < (int)word.size(); ++i) {
                    char original = word[i];
                    for (char c = 'a'; c <= 'z'; ++c) {
                        if (c == original) continue;
                        word[i] = c;

                        // If this transformed word is in the other frontier,
                        // the two BFS fronts have met.
                        if (endSet.count(word)) {
                            return ladder + 1;
                        }
                        // If it's a valid dictionary word, schedule it and
                        // remove from dict to mark as visited.
                        if (dict.count(word)) {
                            nextLevel.insert(word);
                            dict.erase(word);
                        }
                    }
                    word[i] = original; // restore
                }
            }
            beginSet = nextLevel;
            ++ladder;
        }
        return 0; // no transformation sequence found
    }
};

// ---- Local test harness ----
int main() {
    Solution sol;
    string begin = "hit", end = "cog";
    vector<string> wordList = {"hot", "dot", "dog", "lot", "log", "cog"};
    cout << sol.ladderLength(begin, end, wordList) << endl; // 5

    vector<string> wordList2 = {"hot", "dot", "dog", "lot", "log"};
    cout << sol.ladderLength(begin, end, wordList2) << endl; // 0
    return 0;
}
