/**
 * LeetCode 162 - Find Peak Element
 * https://leetcode.com/problems/find-peak-element/
 * Difficulty: Medium
 *
 * Problem:
 * A peak element is an element that is strictly greater than its neighbors.
 * Given a 0-indexed integer array nums, find and return any peak element's
 * index. nums[-1] = nums[n] = -infinity. The solution must run in O(log n)
 * time. You may assume adjacent values are never equal.
 *
 * Approach:
 * Binary search. At each step compare nums[mid] with nums[mid+1]:
 *   - If nums[mid] > nums[mid+1], the descending slope means a peak exists in
 *     the left half (including mid), so search [lo, mid].
 *   - Otherwise the ascending slope means a peak exists in the right half, so
 *     search [mid+1, hi].
 * Because the boundaries are -infinity, a peak is guaranteed, and the loop
 * converges to one in O(log n) time.
 *
 * Complexity:
 * - Time: O(log n)
 * - Space: O(1)
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        int lo = 0;
        int hi = (int)nums.size() - 1;
        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;
            if (nums[mid] > nums[mid + 1]) {
                // Peak is in the left half (mid could be the peak).
                hi = mid;
            } else {
                // Peak is in the right half.
                lo = mid + 1;
            }
        }
        return lo; // lo == hi, a peak index
    }
};

// ---- Local test harness ----
int main() {
    Solution sol;
    vector<int> a = {1, 2, 3, 1};
    cout << sol.findPeakElement(a) << endl; // 2 (nums[2]=3 is a peak)

    vector<int> b = {1, 2, 1, 3, 5, 6, 4};
    cout << sol.findPeakElement(b) << endl; // 1 or 5 (both valid)
    return 0;
}
