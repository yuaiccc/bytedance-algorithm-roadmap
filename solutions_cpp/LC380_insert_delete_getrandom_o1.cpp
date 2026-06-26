/**
 * LeetCode 380 - Insert Delete GetRandom O(1)
 * https://leetcode.com/problems/insert-delete-getrandom/
 * Difficulty: Medium
 *
 * Problem:
 * Implement the RandomizedSet class:
 *   - insert(val): Inserts val into the set if not present. Returns true if
 *     inserted, false otherwise.
 *   - remove(val): Removes val from the set if present. Returns true if
 *     removed, false otherwise.
 *   - getRandom(): Returns a random element from the current set (each element
 *     has equal probability). It is guaranteed that getRandom is only called
 *     when the set is non-empty.
 * All operations must run in average O(1) time.
 *
 * Approach:
 * Combine a dynamic array (vector) with a hash map (value -> index):
 *   - insert: if the value already exists (map lookup), return false. Otherwise
 *     push to the back of the vector and record its index in the map.
 *   - remove: swap-and-pop trick. Move the last element into the slot of the
 *     element to delete, update its index in the map, then pop the back and
 *     erase the deleted value from the map. This keeps vector contiguous and
 *     every operation O(1).
 *   - getRandom: pick a uniformly random index in [0, size) and return it.
 *
 * Complexity:
 * - Time: O(1) average for insert, remove, and getRandom.
 * - Space: O(n) for the vector and the hash map.
 */

#include <bits/stdc++.h>
using namespace std;

class RandomizedSet {
    vector<int> nums;                   // stores the actual values
    unordered_map<int, int> valToIndex; // value -> index in nums

public:
    RandomizedSet() {
        // Seed the RNG so getRandom varies across runs.
        srand((unsigned)time(nullptr));
    }

    bool insert(int val) {
        if (valToIndex.count(val)) return false;
        nums.push_back(val);
        valToIndex[val] = (int)nums.size() - 1;
        return true;
    }

    bool remove(int val) {
        if (!valToIndex.count(val)) return false;

        int idx = valToIndex[val];
        int lastVal = nums.back();

        // Move the last element into the deleted slot (if different).
        nums[idx] = lastVal;
        valToIndex[lastVal] = idx;

        // Remove the now-duplicated tail and the deleted value's entry.
        nums.pop_back();
        valToIndex.erase(val);
        return true;
    }

    int getRandom() {
        return nums[rand() % nums.size()];
    }
};

// ---- Local test harness ----
int main() {
    RandomizedSet rs;
    cout << boolalpha;
    cout << rs.insert(1) << endl;   // true
    cout << rs.remove(2) << endl;   // false
    cout << rs.insert(2) << endl;   // true
    cout << rs.getRandom() << endl; // 1 or 2
    cout << rs.remove(1) << endl;   // true
    cout << rs.insert(2) << endl;   // false (2 already present)
    cout << rs.getRandom() << endl; // 2
    return 0;
}
