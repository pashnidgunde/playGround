/*
 *
 * https://leetcode.com/problems/3sum/
 *
Given an integer array nums, return all the triplets [nums[i], nums[j], nums[k]] such that i != j, i != k, and j != k, and nums[i] + nums[j] + nums[k] == 0.

Notice that the solution set must not contain duplicate triplets.

Example 1:

Input: nums = [-1,0,1,2,-1,-4]
Output: [[-1,-1,2],[-1,0,1]]
Explanation:
nums[0] + nums[1] + nums[2] = (-1) + 0 + 1 = 0.
nums[1] + nums[2] + nums[4] = 0 + 1 + (-1) = 0.
nums[0] + nums[3] + nums[4] = (-1) + 2 + (-1) = 0.
The distinct triplets are [-1,0,1] and [-1,-1,2].
Notice that the order of the output and the order of the triplets does not matter.
Example 2:

Input: nums = [0,1,1]
Output: []
Explanation: The only possible triplet does not sum up to 0.

Example 3:

Input: nums = [0,0,0]
Output: [[0,0,0]]
Explanation: The only possible triplet sums up to 0.
*/

#include <vector>
#include <algorithm>
#include <optional>

using namespace std;
class ThreeSum {
public:

    std::optional<std::pair<int,int>> twoSum(size_t /*index*/, int /*target*/, std::vector<int>& /*nums*/) {
//        size_t begin = index;
//        size_t end = nums.size() - 1;
//
//        while(begin < end) {
//            auto sum = nums[begin] + nums[end];
//            if (sum == target) {
//                return std::make_pair(nums[begin], nums[end]);
//            }
//            else if (sum > target) {
//                end--;
//            }
//            else {
//                begin++;
//            }
//        }
        return std::nullopt;
    }


    vector<vector<int>> threeSum(vector<int>& /*nums*/) {
        vector<vector<int>> result;

//        // sort
//        std::sort(nums.begin(), nums.end());
//
//        size_t index = 1;
//        // skip all duplicates in start
//        while(index < nums.size()) {
//            if (nums[index -1] == nums[index]) {
//                index++;
//            }
//        }
//        index --;
//
//        auto number = nums[index];
//        std::optional<std::pair<int,int>> twoSumPair = twoSum(index, -number, nums);
//        if (twoSumPair.has_value()) {
//            auto& ts = twoSumPair.value();
//            result.emplace_back(number,ts.first,ts.second);
//        }
//
//        index++;
        return result;
    }
};


#include <gtest/gtest.h>
class TestThreeSum : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(TestThreeSum, testCases) {
    {
        std::vector<int> input {-1,0,1,2,-1,-4};
        std::vector<std::vector<int>> expected = {{-1, -1, 2}, {-1, 0, 1}};
        ThreeSum s;
        auto actual = s.threeSum(input);
        EXPECT_EQ(actual.size(), expected.size());
        for (size_t i = 0; i< actual.size(); ++i) {
            EXPECT_EQ(actual[i], expected[i]);
        }
    }
}
