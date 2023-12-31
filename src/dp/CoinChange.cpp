/*
You are given an integer array coins representing coins of different denominations and an integer amount representing a total amount of money.

Return the fewest number of coins that you need to make up that amount. If that amount of money cannot be made up by any combination of the coins, return -1.

You may assume that you have an infinite number of each kind of coin.

Example 1:

Input: coins = [1,2,5], amount = 11
Output: 3
Explanation: 11 = 5 + 5 + 1

Example 2:

Input: coins = [2], amount = 3
Output: -1
Example 3:

Input: coins = [1], amount = 0
Output: 0
*/

#include <vector>
#include <algorithm>
using namespace std;
class CoinChange {
public:

    int coinChange(vector<int>& coins, int amount) {
        std::vector<int> dp;
        std::sort(coins.begin(),coins.end());
        dp.reserve(amount + 1);
        std::fill(dp.begin(), dp.end(), INT_MAX);

        dp[0] = 0;
        for (int i = 1; i<= amount; i++) {
            for (const auto coin : coins) {
                if (coin > i) {
                    continue;
                }
                if (dp[i-coin] == INT_MAX) {
                    continue;
                }
                dp[i] = std::min(dp[i], 1 + dp[i - coin]);
            }
        }
        return dp.back() == INT_MAX ? -1 : dp.back();
    }
};



#include <gtest/gtest.h>
class TestCoinChange : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(TestCoinChange, testCases) {
    CoinChange cc;
    {
        std::vector<int> coins = {1,2,5};
        EXPECT_EQ(cc.coinChange(coins,11), 3);
    }

    {
        std::vector<int> coins = {2};
        EXPECT_EQ(cc.coinChange(coins,3), -1);
    }

    {
        std::vector<int> coins = {1};
        EXPECT_EQ(cc.coinChange(coins,0), 0);
    }

}