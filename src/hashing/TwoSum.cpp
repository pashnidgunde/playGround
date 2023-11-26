// https://leetcode.com/problems/two-sum/
/*
 * Given an array of integers nums and an integer target, return indices of the two numbers such that they add up to target.

You may assume that each input would have exactly one solution, and you may not use the same element twice.

You can return the answer in any order.



Example 1:

Input: nums = [2,7,11,15], target = 9
Output: [0,1]
Explanation: Because nums[0] + nums[1] == 9, we return [0, 1].
Example 2:

Input: nums = [3,2,4], target = 6
Output: [1,2]
Example 3:

Input: nums = [3,3], target = 6
Output: [0,1]
 */

#include <gtest/gtest.h>
#include <vector>
#include <unordered_map>
using namespace std;

struct TwoSum {
    vector<int> twoSum(vector<int>& nums, int target) {
        std::unordered_map<int, int> m;
        for (size_t i =0; i < nums.size(); ++i) {
            auto it = m.find(target -  nums[i]);
            if ( it != m.end()) {
                return {it->second, static_cast<int>(i)};
            }
            m.emplace(nums[i], i);
        }
        return {};
    }
};


class TestTwoSum : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(TestTwoSum, testCases) {
    TwoSum ts;
    {
        auto input = std::vector<int>{2, 7, 11, 15};
        auto actual = ts.twoSum(input, 9);
        auto expected = std::vector<int>{0, 1};
        GTEST_ASSERT_EQ(expected, actual);
    }
    {
        auto input = std::vector<int>{3,2,4};
        auto actual = ts.twoSum(input, 6);
        auto expected = std::vector<int>{1, 2};
        GTEST_ASSERT_EQ(expected, actual);
    }
    {
        auto input = std::vector<int>{3,3};
        auto actual = ts.twoSum(input, 6);
        auto expected = std::vector<int>{0,1};
        GTEST_ASSERT_EQ(expected, actual);
    }
}