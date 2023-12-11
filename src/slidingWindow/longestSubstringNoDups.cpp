// https://leetcode.com/problems/longest-substring-without-repeating-characters/
// https://www.youtube.com/watch?v=wiGpQwVHdE0
/*
 Given a string s, find the length of the longest 
substring
 without repeating characters.

 

Example 1:

Input: s = "abcabcbb"
Output: 3
Explanation: The answer is "abc", with the length of 3.
Example 2:

Input: s = "bbbbb"
Output: 1
Explanation: The answer is "b", with the length of 1.
Example 3:

Input: s = "pwwkew"
Output: 3
Explanation: The answer is "wke", with the length of 3.
Notice that the answer must be a substring, "pwke" is a subsequence and not a substring.

 */

#include <gtest/gtest.h>
#include <climits>
#include <unordered_set>
#include <algorithm>

using namespace std;

class LongestSubstring {
public:

    template<typename Iter>
    auto longestSubString(Iter begin, Iter end) {
        std::unordered_set<char> lookup;
        auto l = begin;
        size_t result = 0;
        while (begin != end) {
            char currentChar = *begin;
            if(lookup.find(currentChar) == lookup.end()) {
                lookup.insert(currentChar);
                result = std::max(result, lookup.size());
                begin++;
            } else {
                lookup.erase(*l);
                l++;
            }
        }
        return result;
    }


    int lengthOfLongestSubstring(string s) {
        return longestSubString(s.begin(), s.end());
    }
};


class TestLongestSubstring : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(TestLongestSubstring, testCases) {
    LongestSubstring instance;
    GTEST_ASSERT_EQ(3, instance.lengthOfLongestSubstring("abcabcbb"));
    GTEST_ASSERT_EQ(3, instance.lengthOfLongestSubstring("pwwkew"));
    GTEST_ASSERT_EQ(1, instance.lengthOfLongestSubstring("bbbbb"));
}