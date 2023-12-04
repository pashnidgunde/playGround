/*
Given an integer array nums, find the
subarray
 with the largest sum, and return its sum.

Example 1:

Input: nums = [-2,1,-3,4,-1,2,1,-5,4]
Output: 6
Explanation: The subarray [4,-1,2,1] has the largest sum 6.
Example 2:

Input: nums = [1]
Output: 1
Explanation: The subarray [1] has the largest sum 1.
Example 3:

Input: nums = [5,4,-1,7,8]
Output: 23
Explanation: The subarray [5,4,-1,7,8] has the largest sum 23.

*/

// https://www.youtube.com/watch?v=5WZl3MMT0Eg&list=PLot-Xpze53ldVwtstag2TL4HQhAnC8ATf&index=5

#include <vector>
#include <gtest/gtest.h>

using namespace std;

class MaxSubArray {
public:
    // O(n*n)
    int maxSubArray1(vector<int>& nums) {
        int maxSoFar = INT_MIN;
        for (size_t i = 0; i < nums.size(); ++i) {
            int sumSoFar = 0;
            for (size_t j = i; j < nums.size(); ++j) {
                sumSoFar += nums[j];
                maxSoFar = std::max(maxSoFar, sumSoFar);
            }
        }
        return maxSoFar;
    }

    // O(n)
    int maxSubArray(vector<int>& nums) {
        int maxSoFar = INT_MIN;
        int sumSoFar = 0;
        for (int num : nums) {
            sumSoFar += num;
            maxSoFar = std::max(maxSoFar, sumSoFar);
            if (sumSoFar < 0) {
                sumSoFar = 0;
            }
        }
        return maxSoFar;
    }
};

class TestMaxSubArray : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(TestMaxSubArray, testCases) {
    MaxSubArray instance;
    {
        auto input = std::vector<int>{-2,1,-3,4,-1,2,1,-5,4};
        auto actual = instance.maxSubArray(input);
        GTEST_ASSERT_EQ(6, actual);
    }
    {
        auto input = std::vector<int>{1};
        auto actual = instance.maxSubArray(input);
        GTEST_ASSERT_EQ(1, actual);
    }
    {
        auto input = std::vector<int>{5,4,-1,7,8};
        auto actual = instance.maxSubArray(input);
        GTEST_ASSERT_EQ(23, actual);
    }
    {
        auto input = std::vector<int>{-1};
        auto actual = instance.maxSubArray(input);
        GTEST_ASSERT_EQ(-1, actual);
    }
    {
        auto input = std::vector<int>{0, -1, -2};
        auto actual = instance.maxSubArray(input);
        GTEST_ASSERT_EQ(0, actual);
    }
    {
        auto input = std::vector<int>{-2, -1};
        auto actual = instance.maxSubArray(input);
        GTEST_ASSERT_EQ(-1, actual);
    }
}
