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
    template<typename IterT, typename Target>
    std::vector<std::pair<IterT,IterT>> twoSum(IterT b, IterT e, Target target) {
        std::vector<std::pair<IterT,IterT>> result;
        auto begin{b};
        auto end{e};
        end--;
        while(begin < end) {
            auto sum{*begin + *end};
            if (sum == target) {
                result.emplace_back(begin,end);
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

    // {1,1,1,1,1,1,1}
    auto skipDuplicates(auto begin, auto end) {
      if (begin == end) {
        return end;
      }
      auto next{begin + 1};
      while(next != end && *begin == *next) {
          next++;
      }
      return next;
    }

    template<typename IterT, typename Target>
    std::vector<std::vector<int>> threeSum(IterT begin, IterT end, Target target) {
        if (begin == end) {
          return {{}};
        }

        // sort
        // e.g. {-4,-1,-1,0,1,2};
        std::sort(begin,end);

        vector<vector<int>> result;
        while(begin != end) {
          //std::cout << "At StartIter : " << *begin << std::endl;
          //std::cout << "Target : " << target << std::endl;
          //std::cout << "TwoSum target : " << target - *begin << std::endl;

          auto sumPair{twoSum(begin + 1, end, target - *begin)};
          //std::cout << "----" << std::endl;
          for(const auto& pair : sumPair) {
            //std::cout << "pair : " << *pair.first << ", " << *pair.second << std::endl;
            result.emplace_back(std::vector<int>{static_cast<int>(*begin),
                                                 static_cast<int>(*pair.first),
                                                 static_cast<int>(*pair.second)});
          }
          // std::cout << "----" << std::endl;
          begin = skipDuplicates(begin,end);
        }

        return result;
    }

    vector<vector<int>> threeSum(vector<int>& nums, int target) {
      return threeSum(nums.begin(), nums.end(), target);
    }
};


#include <gtest/gtest.h>
class TestThreeSum : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

//template<typename IterT>
//bool rangeCompare(const std::vector<std::pair<IterT,IterT>>& lhs,
//                  const std::vector<std::pair<IterT,IterT>>& rhs) {
//  if (lhs.size() != rhs.size()) {
//    return false;
//  }
//
//  auto lIter{lhs.begin()};
//  auto rIter{lhs.begin()};
//
//  while(lIter != lhs.end() && rIter != rhs.end()) {
//    auto& lhsPair{*lIter};
//    auto& rhsPair{*rIter};
//
//    if (*lhsPair.first != *rhsPair.first &&
//        *lhsPair.second != *rhsPair.second) {
//      return false;
//    }
//    ++lIter;
//    ++rIter;
//
//
//  return lhs == rhs;
//}


TEST_F(TestThreeSum, twoSumTests) {
    ThreeSum ts;
    using IterT = std::vector<int>::iterator;
    using IterPair = std::pair<IterT,IterT>;
    using ListIterPair = std::vector<IterPair>;
    {
        auto input{std::vector<int>{2, 7, 11, 15}};
        ListIterPair actual{ts.twoSum(input.begin(), input.end(),9)};
        ListIterPair expected{{input.begin(), input.begin() + 1}};
        // EXPECT_TRUE(rangeCompare(expected, actual));
        EXPECT_EQ(expected, actual);
    }
    
    {
        auto input{std::vector<int>{2,3,4}};
        ListIterPair actual{ts.twoSum(input.begin(), input.end(), 6)};
        ListIterPair expected{{input.begin(), input.begin() + 2}};
        EXPECT_EQ(expected, actual);
    }
    {
        auto input{std::vector<int>{3,3}};
        ListIterPair actual{ts.twoSum(input.begin(), input.end(), 6)};
        ListIterPair expected{{input.begin(),input.begin() + 1}};
        EXPECT_EQ(expected, actual);
    }
    {
      auto input{std::vector<int>{3,3}};
      ListIterPair actual{ts.twoSum(input.begin(), input.end(), 5)};
      EXPECT_TRUE(actual.empty());
    }
}

TEST_F(TestThreeSum, testSkipAtStart) {
  ThreeSum ts;
  {
    auto input = std::vector<int>{};
    EXPECT_EQ(ts.skipDuplicates(input.begin(), input.end()), input.end());
  }

  {
    auto input = std::vector<int>{1,1,1,1,1,1,1};
    auto iter = ts.skipDuplicates(input.begin(), input.end());
    EXPECT_EQ(iter, input.end());
  }

  {
    std::vector<int> input{1,2,3};
    auto iter = ts.skipDuplicates(input.begin(), input.end());
    EXPECT_EQ(iter, input.begin() + 1);
  }

}

TEST_F(TestThreeSum, testCases) {
    {
        std::vector<int> input {-1,0,1,2,-1,-4};
        std::vector<std::vector<int>> expected = {{-1, -1, 2}, {-1, 0, 1}};
        ThreeSum s;
        auto actual = s.threeSum(input,0);
        EXPECT_EQ(actual.size(), expected.size());
        for (size_t i = 0; i< actual.size(); ++i) {
            EXPECT_EQ(actual[i], expected[i]);
        }
    }
}
