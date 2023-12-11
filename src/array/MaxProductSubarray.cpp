// https://leetcode.com/problems/maximum-product-subarray/
/*
 * Given an integer array nums, find a
subarray
 that has the largest product, and return the product.

The test cases are generated so that the answer will fit in a 32-bit integer.

Example 1:

Input: nums = [2,3,-2,4]
Output: 6
Explanation: [2,3] has the largest product 6.
Example 2:

Input: nums = [-2,0,-1]
Output: 0
Explanation: The result cannot be 2, because [-2,-1] is not a subarray.
 */

#include <vector>
#include <climits>
#include <gtest/gtest.h>

using namespace std;

class MaxProductSubArray {
public:
    //O(n*n)
    int maxProductSubArray1(vector<int>& nums) {
        int maxProduct = 0;
        for(size_t i = 0; i< nums.size(); ++i) {
            int maxProductSubArray = 1;
            for (size_t j = i; j < nums.size(); ++j) {
                maxProductSubArray = maxProductSubArray * nums[j];
                maxProduct = std::max(maxProductSubArray, maxProduct);
            }
        }
        return maxProduct;
    }

    //O(n)
    int maxProductSubArray(vector<int>& nums) {
        int rMin = 1;
        int rMax = 1;
        int maxResult = INT_MIN;
        int maxBetweenZeros = INT_MIN;
        auto reset = [&](){
            rMin = 1;
            rMax = 1;
            maxResult = std::max(maxResult, maxBetweenZeros);
            maxBetweenZeros = 0;
        };

        for (const int num : nums) {
            if (num == 0) {
                reset();
                continue;
            }

            // keep running min and max
            int temp = rMin * num;
            rMin = rMin * num;
            rMax = rMax * num;

            // determine new min and max after calculation,
            // because a negative number will change rMin and rMax
            rMin = std::min(rMin, rMax);
            rMax = std::max(temp, rMax);

            // the current number could be greater than calculated min and max
            rMin = std::min(rMin, num);
            rMax = std::max(rMax, num);

            maxBetweenZeros = std::max(rMax, maxBetweenZeros);
        }

        return std::max(maxResult, maxBetweenZeros);
    }
};

class TestMaxProductSubArray : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(TestMaxProductSubArray, testCases) {
    MaxProductSubArray instance;
    {
        auto input = std::vector<int>{2,3,-2,4};
        auto actual = instance.maxProductSubArray(input);
        GTEST_ASSERT_EQ(6, actual);
    }
    {
        auto input = std::vector<int>{-2,0,-1};
        auto actual = instance.maxProductSubArray(input);
        GTEST_ASSERT_EQ(0, actual);
    }
    {
        auto input = std::vector<int>{-2};
        auto actual = instance.maxProductSubArray(input);
        GTEST_ASSERT_EQ(-2, actual);
    }
    {
        auto input = std::vector<int>{1,-3,4};
        auto actual = instance.maxProductSubArray(input);
        GTEST_ASSERT_EQ(4, actual);
    }
    {
        auto input = std::vector<int>{-2,3,-4};
        auto actual = instance.maxProductSubArray(input);
        GTEST_ASSERT_EQ(24, actual);
    }
    {
        auto input = std::vector<int>{6,3,-10,0,2};
        auto actual = instance.maxProductSubArray(input);
        GTEST_ASSERT_EQ(18, actual);
    }
}