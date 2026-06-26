/**
 * LeetCode 121 - Best Time to Buy and Sell Stock
 * https://leetcode.com/problems/best-time-to-buy-and-sell-stock/
 * Difficulty: Easy
 *
 * Problem:
 * You are given an array prices where prices[i] is the price of a given stock
 * on day i. You want to maximize your profit by choosing a single day to buy
 * one stock and choosing a different day in the future to sell that stock.
 * Return the maximum profit you can achieve. If you cannot achieve any profit,
 * return 0.
 *
 * Approach:
 * Single pass: keep track of the minimum price seen so far (minPrice), and at
 * each day compute the profit if we sell today (price - minPrice). Update the
 * maximum profit accordingly. This simulates buying at the cheapest point
 * before the current day and selling today.
 *
 * Complexity:
 * - Time: O(n) — single pass.
 * - Space: O(1) — only two variables.
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int minPrice = INT_MAX;
        int maxProfit = 0;
        for (int price : prices) {
            if (price < minPrice) {
                minPrice = price;          // potential buy day
            } else {
                int profit = price - minPrice; // potential sell today
                if (profit > maxProfit) {
                    maxProfit = profit;
                }
            }
        }
        return maxProfit;
    }
};

// Optional: quick test
// int main() {
//     Solution s;
//     vector<int> prices = {7, 1, 5, 3, 6, 4};
//     cout << s.maxProfit(prices) << endl; // 5
//     return 0;
// }
