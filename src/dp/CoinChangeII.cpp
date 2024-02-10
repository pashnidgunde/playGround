/*
https://leetcode.com/problems/coin-change-ii/

You are given an integer array coins representing coins of different denominations and an integer amount representing a total amount of money.

Return the number of combinations that make up that amount. If that amount of money cannot be made up by any combination of the coins, return 0.

You may assume that you have an infinite number of each kind of coin.

The answer is guaranteed to fit into a signed 32-bit integer.

 

Example 1:

Input: amount = 5, coins = [1,2,5]
Output: 4
Explanation: there are four ways to make up the amount:
5=5
5=2+2+1
5=2+1+1+1
5=1+1+1+1+1
Example 2:

Input: amount = 3, coins = [2]
Output: 0
Explanation: the amount of 3 cannot be made up just with coins of 2.
Example 3:

Input: amount = 10, coins = [10]
Output: 1

*/

#include <vector>
#include <algorithm>
#include <climits>
#include <gtest/gtest.h>

using namespace std;
class CoinChangeII {
public:
    int solveRecursive(const std::vector<int>& coins, const int amount, size_t index) {
        if (amount < 0) {
            return 0;
        }

        if (index == coins.size()) {
            return 0;
        }

        if (0 == amount) {
            return 1;
        }

        int ways = 0;
        for (size_t i=index; i < coins.size(); i++) {
            if (amount >= coins[i]) {
                ways += solveRecursive(coins, amount - coins[i], i);
            }
        }

        return ways;
    }


    int coinChange(vector<int>& coins, int amount) {
        return solveRecursive(coins,amount,0);
    }
};

class TestCoinChangeII : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(TestCoinChangeII, testCases) {
    CoinChangeII cc;
    {
        std::vector<int> coins = {1,2,5};
        EXPECT_EQ(cc.coinChange(coins,5), 4);
    }

    {
        std::vector<int> coins = {2};
        EXPECT_EQ(cc.coinChange(coins,3), 0);
    }

    {
        std::vector<int> coins = {10};
        EXPECT_EQ(cc.coinChange(coins,10), 1);
    }

}