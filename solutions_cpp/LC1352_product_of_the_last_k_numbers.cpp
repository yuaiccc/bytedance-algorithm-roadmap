/**
 * LeetCode 1352 - Product of the Last K Numbers
 * https://leetcode.com/problems/product-of-the-last-k-numbers/
 * Difficulty: Medium
 *
 * Problem:
 * Design a data structure that supports two operations on a stream of integers:
 *   add(int num) — append num to the stream.
 *   getProduct(int k) — return the product of the last k numbers.
 * It is guaranteed that the current stream has at least k numbers, and
 * getProduct will be called with k >= 1.
 *
 * Approach:
 * Maintain a prefix-product array `pp` where pp[i] is the product of the first
 * i numbers added. Then getProduct(k) = pp[n] / pp[n - k]. The catch: if a zero
 * is added, division breaks. We handle this by resetting the prefix-product
 * array whenever a 0 is encountered (start a new segment with pp = {1}). Since
 * any query spanning a zero would yield 0, we just check: if k >= size of the
 * current prefix array, the last k numbers contain a zero, so return 0.
 *
 * Complexity:
 * - add:        O(1) amortized.
 * - getProduct: O(1).
 * - Space: O(n) for the prefix-product array.
 */

#include <bits/stdc++.h>
using namespace std;

class ProductOfNumbers {
public:
    ProductOfNumbers() {
        // pp[0] = 1 acts as the multiplicative identity.
        pp.push_back(1);
    }

    void add(int num) {
        if (num == 0) {
            // Reset: any product spanning across this zero is zero.
            pp.clear();
            pp.push_back(1);
        } else {
            pp.push_back(pp.back() * num);
        }
    }

    int getProduct(int k) {
        int n = (int)pp.size() - 1; // number of real elements in current segment
        if (k > n) {
            // The window of the last k numbers crosses a zero reset.
            return 0;
        }
        return pp[n] / pp[n - k];
    }

private:
    vector<int> pp; // prefix products, pp[0] = 1
};

/**
 * Your ProductOfNumbers object will be instantiated and called as such:
 * ProductOfNumbers* obj = new ProductOfNumbers();
 * obj->add(num);
 * int param_2 = obj->getProduct(k);
 */

// Optional: quick test
// int main() {
//     ProductOfNumbers p;
//     p.add(3); p.add(0); p.add(2); p.add(5); p.add(4);
//     cout << p.getProduct(2) << endl; // 20
//     cout << p.getProduct(3) << endl; // 40
//     cout << p.getProduct(4) << endl; // 0
//     return 0;
// }
