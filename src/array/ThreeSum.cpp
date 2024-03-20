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
using Index = int;
using IndexPair = std::pair<Index,Index>;

class ThreeSum {
public:
    template<typename Iter, typename Target>
    std::vector<IndexPair> twoSum(Iter b, Iter e, Target target) {
        std::vector<IndexPair> result;
        auto begin = b;
        auto end = e;
        end--;
        while(begin < end) {
            auto sum = *begin + *end;
            if (sum == target) {
                auto bd = std::distance(b,begin);
                auto ed = std::distance(b,end);
                result.emplace_back(bd,ed);
                begin++;
            }
            else if (sum > target) {
                end--;
            }
            else {
                begin++;
            }
        }
        return result;
    }

    template<typename Iter, typename Target>
    std::vector<std::vector<int>> threeSum(Iter begin, Iter end, Target target) {
        // sort
        std::sort(begin,end);

        auto b = begin++;
        // skip all duplicates in start
        while(index < nums.size()) {
            if (nums[index -1] == nums[index]) {
                index++;
            }
        }
        index --;

        return {{}};
    }

    
    auto skipDuplicatesAtStart(auto begin, auto end) {
        if (begin == end) {
            return end;
        }

        auto b = begin;
        b++;
        while (b != end) {
            if (*begin == *b) {
                b++;
            }
        }
        b--;
        return b;
    }

    // {-1,0,1,2,-1,-4};
    // {-4,-1,-1,0,1,2};
    vector<vector<int>> threeSum(vector<int>& /*nums*/, int /*target*/) {
        // sort
        // std::sort(nums.begin(), nums.end());

        // auto begin = nums.begin();
        // auto end = nums.end();
        
        // auto start = skipDuplicatesAtStart(begin,end);

        vector<vector<int>> result;
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


TEST_F(TestThreeSum, twoSumTests) {
    ThreeSum ts;
    {
        auto input = std::vector<int>{2, 7, 11, 15};
        auto actual = ts.twoSum(input.begin(), input.end(),9);
        auto expected = std::vector<IndexPair>{{0, 1}};
        GTEST_ASSERT_EQ(expected, actual);
    }
    
    {
        auto input = std::vector<int>{2,3,4};
        auto actual = ts.twoSum(input.begin(), input.end(), 6);
        auto expected = std::vector<IndexPair>{{0, 2}};
        GTEST_ASSERT_EQ(expected, actual);
    }
    {
        auto input = std::vector<int>{3,3};
        auto actual = ts.twoSum(input.begin(), input.end(), 6);
        auto expected = std::vector<IndexPair>{{0,1}};
        GTEST_ASSERT_EQ(expected, actual);
    }
}

//TEST_F(TestThreeSum, testCases) {
//    {
//        std::vector<int> input {-1,0,1,2,-1,-4};
//        std::vector<std::vector<int>> expected = {{-1, -1, 2}, {-1, 0, 1}};
//        ThreeSum s;
//        auto actual = s.threeSum(input,0);
//        EXPECT_EQ(actual.size(), expected.size());
//        for (size_t i = 0; i< actual.size(); ++i) {
//            EXPECT_EQ(actual[i], expected[i]);
//        }
//    }
//}
