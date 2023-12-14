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
#include <vector>

class ClimbingStairsTopDown {
    private:
        static int climbRecursive(int N, int current) {
            if (current == N) {
                return 1;
            }
            if (current > N) {
                return 0;
            }

            return climbRecursive(N-1, current) +  climbRecursive(N-2, current);
        }

    public:
        static int climb(int N) {
            return climbRecursive(N,0);
        }
};

class ClimbingStairsMemoized {
    private:
        // Remember old computed state
        static int climbRecursive(int N, int current, std::vector<int>& previouslyDetermined) {
            if (current == N) {
                return 1;
            }
            if (current > N) {
                return 0;
            }

            if (previouslyDetermined[current] != -1) {
                return previouslyDetermined[current];
            }

            previouslyDetermined[current] = 
                climbRecursive(N, current + 1 ,previouslyDetermined) 
                +  climbRecursive(N, current + 2, previouslyDetermined);
            
            return previouslyDetermined[current];
        }
    public:
        static int climb(int N) {
            std::vector<int> previouslyDetermined(N+1, -1);
            return climbRecursive(N,0, previouslyDetermined);
        }
};

class ClimbingStairsBottomUp {
    public:
        static int climb(int N) {
            std::vector<int> store(N + 1 , -1);
            int currIndex = N - 1;
            store[currIndex] = 0;
            store[currIndex--] = 1;
            store[currIndex--] = 2;

            while(currIndex >= 0) {
                store[currIndex] = store[currIndex+1] + store[currIndex+2];
                currIndex--;
            }

            return store[0];
        }
};

class CSSpaceEfficient {
    public:
        // Bottom up
        // Need to keep track of last two steps
        static int climb(int n) {
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
    {
        EXPECT_EQ(ClimbingStairsTopDown::climb(2), 2);
        EXPECT_EQ(ClimbingStairsTopDown::climb(3), 3);
        EXPECT_EQ(ClimbingStairsTopDown::climb(5), 8);
        //EXPECT_EQ(cs.climbStairsTopDown(45), 1836311903);
    }

    {
        EXPECT_EQ(ClimbingStairsMemoized::climb(2), 2);
        EXPECT_EQ(ClimbingStairsMemoized::climb(3), 3);
        EXPECT_EQ(ClimbingStairsMemoized::climb(5), 8);
        EXPECT_EQ(ClimbingStairsMemoized::climb(45), 1836311903);
    }

    {
        EXPECT_EQ(ClimbingStairsBottomUp::climb(2), 2);
        EXPECT_EQ(ClimbingStairsBottomUp::climb(3), 3);
        EXPECT_EQ(ClimbingStairsBottomUp::climb(5), 8);
        EXPECT_EQ(ClimbingStairsBottomUp::climb(45), 1836311903);
    }

    {
        EXPECT_EQ(CSSpaceEfficient::climb(2), 2);
        EXPECT_EQ(CSSpaceEfficient::climb(3), 3);
        EXPECT_EQ(CSSpaceEfficient::climb(5), 8);
        EXPECT_EQ(CSSpaceEfficient::climb(45), 1836311903);
    }

    
}