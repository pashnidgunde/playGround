/*
 * https://leetcode.com/problems/climbing-stairs/
 * You are climbing a staircase. It takes n steps to reach the top.

    Each time you can either climb 1 or 2 steps. In how many distinct ways can you climb to the top?

    Input: n = 2
    Output: 2
    Explanation: There are two ways to climb to the top.
    1. 1 step + 1 step
    2. 2 steps

    Input: n = 3
    Output: 3
    Explanation: There are three ways to climb to the top.
    1. 1 step + 1 step + 1 step
    2. 1 step + 2 steps
    3. 2 steps + 1 step
 *
 */
#include <unordered_map>

class ClimbingStairs {
public:
    std::unordered_map<int,long long> cache {
            {1,1},
            {2,2}
    };

    int climbStairs(int n) {
        auto it = cache.find(n);
        if (it != cache.end()) {
            return it->second;
        }
        cache[n] = climbStairs(n-1) + climbStairs(n-2);
        return cache[n];
    }

    // Bottom up
    // Need to keep track of last two steps
    int fibonacci(int n) {
        if (n == 1) return 1;
        if (n == 2) return 2;
        int first = 1;
        int second = 2;
        auto steps = 0;
        for (int j = 3; j <= n; j++) {
            steps = first + second;
            first = second;
            second = steps;
        }
        return steps;
    }
};

#include <gtest/gtest.h>
class TestClimbingStairs : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(TestClimbingStairs, testCases) {
    ClimbingStairs cs;
    {
        EXPECT_EQ(cs.climbStairs(2), 2);
        EXPECT_EQ(cs.fibonacci(2), 2);
    }
    {
        EXPECT_EQ(cs.climbStairs(3), 3);
        EXPECT_EQ(cs.fibonacci(3), 3);
    }
    {
        EXPECT_EQ(cs.climbStairs(45), 1836311903);
        EXPECT_EQ(cs.fibonacci(45), 1836311903);
    }
}