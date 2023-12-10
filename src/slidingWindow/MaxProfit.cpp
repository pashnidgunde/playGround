// https://leetcode.com/problems/best-time-to-buy-and-sell-stock/
// https://www.youtube.com/watch?v=1pkOgXD63yU&list=PLot-Xpze53ldVwtstag2TL4HQhAnC8ATf&index=2
/*
 * You are given an array prices where prices[i] is the price of a given stock on the ith day.

You want to maximize your profit by choosing a single day to buy one stock and choosing a different day in the future to sell that stock.

Return the maximum profit you can achieve from this transaction. If you cannot achieve any profit, return 0.



Example 1:

Input: prices = [7,1,5,3,6,4]
Output: 5
Explanation: Buy on day 2 (price = 1) and sell on day 5 (price = 6), profit = 6-1 = 5.
Note that buying on day 2 and selling on day 1 is not allowed because you must buy before you sell.
Example 2:

Input: prices = [7,6,4,3,1]
Output: 0
Explanation: In this case, no transactions are done and the max profit = 0.
 */

#include <gtest/gtest.h>
#include <climits>
using namespace std;

struct TestMaxProfit {
    int maxProfit(vector<int>& prices) {
        auto bIter =  prices.begin();
        auto sIter = prices.begin();
        auto maxProfitSoFar = INT_MIN;
        while(sIter != prices.end()) {
            auto profit = *sIter - *bIter;
            maxProfitSoFar = std::max(maxProfitSoFar, profit);
            if (profit < 0) {
                bIter = sIter;
            }
            sIter++;
        }
        return maxProfitSoFar;
    }
};


class TestTestMaxProfit : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(TestTestMaxProfit, testCases) {
    TestMaxProfit instance;
    {
        auto input = std::vector<int>{7,1,5,3,6,4};
        auto actual = instance.maxProfit(input);
        GTEST_ASSERT_EQ(5, actual);
    }
    {
        auto input = std::vector<int>{7,6,4,3,1};
        auto actual = instance.maxProfit(input);
        GTEST_ASSERT_EQ(0, actual);
    }
}