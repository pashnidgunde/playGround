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
#include <iostream>
#include <climits>

using namespace std;

class CoinChangeRec {

public:
    int coinChangeRecursive(vector<int> &coins, int amount) {
        if (amount < 0) {
            return INT_MAX;
        }
        if (amount == 0) {
            return 0;
        }
        int noc = INT_MAX;
        for (const int coin : coins ) {
            int ans = coinChangeRecursive(coins, amount - coin);
            if (ans != INT_MAX) {
                noc = std::min(noc, 1 + ans);
            }
        }
        return noc;
    }

    int coinChange(vector<int> &coins, int amount) {
        int ret = coinChangeRecursive(coins, amount);
        if (ret == INT_MAX) {
            return -1;
        }
        return ret;
    }
};

class CoinChangeDP {
public:
    int coinChange(const std::vector<int>& coins, int amount) {
        std::vector<int> result(amount + 1, INT_MAX);
        result[0] = 0;
        for (size_t i=1; i < result.size(); i++) {
            for (const auto coin : coins) {
                int index = static_cast<int>(i - coin);
                if (index >= 0 && result[index] != INT_MAX) {
                    result[i] = std::min(result[i], 1 + result[index]);
                }
            }
        }

        return result[amount] == INT_MAX ? -1 : result[amount];
    }


};



#include <gtest/gtest.h>
class TestCoinChange : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(TestCoinChange, testCases) {
    CoinChangeRec coinChangeRec;
    CoinChangeDP coinChangeDp;
    {
        std::vector<int> coins = {1,2,5};
        EXPECT_EQ(coinChangeRec.coinChange(coins,11), 3);
        EXPECT_EQ(coinChangeDp.coinChange(coins,11), 3);

    }

    {
        std::vector<int> coins = {2};
        EXPECT_EQ(coinChangeRec.coinChange(coins,3), -1);
        EXPECT_EQ(coinChangeDp.coinChange(coins,3), -1);
    }

    {
        std::vector<int> coins = {1};
        EXPECT_EQ(coinChangeRec.coinChange(coins,0), 0);
        EXPECT_EQ(coinChangeDp.coinChange(coins,0), 0);
    }

}
