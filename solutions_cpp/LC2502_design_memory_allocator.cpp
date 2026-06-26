/**
 * LeetCode 2502 - Design Memory Allocator
 * https://leetcode.com/problems/design-memory-allocator/
 * Difficulty: Medium
 *
 * Problem:
 * Design an Allocator class over an array of n memory units (0-indexed).
 *   - Allocator(int n): creates an array of size n, all units free (marked 0).
 *   - int allocate(int size, int mID): find the leftmost block of `size`
 *     consecutive free memory units and mark them with mID. Return the first
 *     index of the block, or -1 if no such block exists.
 *   - int free(int mID): free all memory units assigned to mID and return the
 *     number of units freed.
 *
 * Approach:
 * Use a single vector<int> of length n where 0 means free and a positive mID
 * means allocated to that ID.
 *   - allocate: scan left to right tracking a run of consecutive free units.
 *     When the run reaches `size`, assign mID and return the start index.
 *   - free: scan the whole array counting and zeroing units equal to mID.
 * This straightforward approach is O(n) per operation, which is acceptable
 * for the problem constraints.
 *
 * Complexity:
 * - Time: O(n) per allocate and O(n) per free.
 * - Space: O(n) for the memory array.
 */

#include <bits/stdc++.h>
using namespace std;

class Allocator {
    vector<int> memory; // 0 = free, otherwise stores the mID

public:
    Allocator(int n) : memory(n, 0) {}

    int allocate(int size, int mID) {
        int run = 0;       // current consecutive free units
        int start = -1;    // start index of the current run
        for (int i = 0; i < (int)memory.size(); ++i) {
            if (memory[i] == 0) {
                if (run == 0) start = i;
                ++run;
                if (run == size) {
                    // Found a big-enough block; mark it.
                    for (int j = start; j < start + size; ++j)
                        memory[j] = mID;
                    return start;
                }
            } else {
                run = 0; // reset the run on an occupied unit
            }
        }
        return -1; // not enough contiguous free space
    }

    int free(int mID) {
        int freed = 0;
        for (int i = 0; i < (int)memory.size(); ++i) {
            if (memory[i] == mID) {
                memory[i] = 0;
                ++freed;
            }
        }
        return freed;
    }
};

// ---- Local test harness ----
int main() {
    // Example from the problem:
    // ["Allocator","allocate","allocate","allocate","free","allocate","allocate","free"]
    // [[10],[1,1],[1,2],[1,3],[2],[3,4],[1,1],[1]]
    Allocator alloc(10);
    cout << alloc.allocate(1, 1) << endl; // 0
    cout << alloc.allocate(1, 2) << endl; // 1
    cout << alloc.allocate(1, 3) << endl; // 2
    cout << alloc.free(2) << endl;        // 1
    cout << alloc.allocate(3, 4) << endl; // 3
    cout << alloc.allocate(1, 1) << endl; // 1
    cout << alloc.free(1) << endl;        // 2
    return 0;
}
