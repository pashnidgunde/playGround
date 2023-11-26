/*
Given an integer array nums, return an array answer such that answer[i] is equal to the product of all the elements of nums except nums[i].

The product of any prefix or suffix of nums is guaranteed to fit in a 32-bit integer.

You must write an algorithm that runs in O(n) time and without using the division operation.



Example 1:

Input: nums = [1,2,3,4]
Output: [24,12,8,6]
Example 2:

Input: nums = [-1,1,0,-3,3]
Output: [0,0,9,0,0]
*/

#include <vector>
#include <gtest/gtest.h>
#include "internal/Utils.h"

using namespace std;

class ProductExceptSelf {
public:
    // Note , without using division operator
    // keep 2 vectors , pre and post that keeps product at each level
    vector<int> productExceptSelf(vector<int>& nums) {
        // pre
        std::vector<int> pre(nums.size());
        pre[0] = 1;
        for (size_t i = 1 ; i < nums.size(); i++) {
            pre[i] =  pre[i-1] * nums[i-1];
        }
        std::cout << pre << std::endl;

        // post
        std::vector<int> post(nums.size());
        post[nums.size()-1] = 1;
        for (int i = static_cast<int>(nums.size()-2); i >= 0; i--) {
            post[i] =  post[i+1] * nums[i+1];
        }
        std::cout << pre << std::endl;

        std::vector<int> result(nums.size());
        for (size_t i = 0; i < nums.size(); ++i) {
            result[i] = pre[i] * post[i];
        }
        std::cout << pre << std::endl;
        return result;
    }

    // Note , without using division operator
    // Doing this in one vector
    // Pre and post that keeps product at each level
    // [1,2,3,4]
    // [1,1,2,6] ---> pre at each level
    // [,,,6] --> Starting in reverse order, post = 1 at 4
    // [,,8,6] --> post 4 at 3 and pre = 2 , so product = 8
    // [,12,8,6] --> post 12 at 2 and pre = 1 , so product = 12
    // [24,12,8,6] --> post 24 at 1 and pre = 1 , so product = 24
    vector<int> productExceptSelf1(vector<int>& nums) {
        // pre
        std::vector<int> result(nums.size());
        result[0] = 1;
        for (size_t i = 1 ; i < nums.size(); i++) {
            result[i] =  result[i-1] * nums[i-1];
        }
        std::cout << result << std::endl;

        // post
        auto post = 1;
        for (int i = static_cast<int>(nums.size()-1); i >= 0; i--) {
            result[i] = result[i] * post;
            post = post * nums[i];
        }
        std::cout << result << std::endl;
        return result;
    }
};

class TestProductExceptSelf : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(TestProductExceptSelf, testCases) {
    ProductExceptSelf instance;
    {
        auto input = std::vector<int>{1,2,3,4};
        auto expected = std::vector<int>{24,12,8,6};
        auto actual = instance.productExceptSelf1(input);
        GTEST_ASSERT_EQ(expected, actual);
    }
    {
        auto input = std::vector<int>{-1,1,0,-3,3};
        auto expected = std::vector<int>{0,0,9,0,0};
        auto actual = instance.productExceptSelf1(input);
        GTEST_ASSERT_EQ(expected, actual);
    }
}