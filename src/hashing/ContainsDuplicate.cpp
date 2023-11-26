// https://leetcode.com/problems/contains-duplicate/

/*
Given an integer array nums, return true if any value appears at least twice in the array, and return false if every element is distinct.
*/

#include <unordered_set>
#include <gtest/gtest.h>
using namespace std;

struct Solution {
    bool containsDuplicate(vector<int>& nums) {
        std::unordered_set<int> s;
        for (const auto num : nums) {
            if (s.find(num) != s.end()) {
                return true;
            }
            s.emplace(num);
        }
        return false;
    }
};


class TestContainsDuplicate : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(TestContainsDuplicate, testCases) {
    Solution instance;
    {
        auto input = std::vector<int>{1,2,3,1};
        auto actual = instance.containsDuplicate(input);
        GTEST_ASSERT_TRUE(actual);
    }
    {
        auto input = std::vector<int>{1,2,3,4};
        auto actual = instance.containsDuplicate(input);
        GTEST_ASSERT_FALSE(actual);
    }
    {
        auto input = std::vector<int>{1,1,1,3,3,4,3,2,4,2};
        auto actual = instance.containsDuplicate(input);
        GTEST_ASSERT_TRUE(actual);
    }

}
