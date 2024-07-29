#include <algorithm>
#include <print>
#include <vector>

namespace pn {
    template<typename Iter, typename T>
    bool contains(Iter begin, Iter end, T val) {
        while(begin != end) {
            if (*begin == val) {
                return true;
            }
            ++begin;
        }
        return false;
    }

    template<typename T>
    bool contains(std::vector<T>& hayStack, const T& needle) {
        return contains(hayStack.begin(), hayStack.end(), needle);
    }

    template<typename Iter>
    bool contains_subrange(Iter hayStackBegin, Iter hayStackEnd, 
        Iter needleBegin, Iter needleEnd) {
        auto needleIter = needleBegin;
        while(hayStackBegin != hayStackEnd && needleIter != needleEnd) {
            if (*needleIter != *hayStackBegin) {
                needleIter = needleBegin;
            } else {
                needleIter++;
            }
            hayStackBegin++;
        }
        return needleIter == needleEnd;
    }


    template<typename T>
    bool contains_subrange(const std::vector<T>& hayStack, const std::vector<T>& needle) {
        return contains_subrange(hayStack.begin(), hayStack.end(), needle.begin(), needle.end());
    }
}

#include <gtest/gtest.h>
class TestContains : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(TestContains, testOne) {
    std::vector<int> v{1,2,3,4,5,6};
    EXPECT_TRUE(std::ranges::contains(v, 4));
    EXPECT_TRUE(pn::contains(v,4));
    EXPECT_FALSE(pn::contains(v,10));
}

TEST_F(TestContains, testRange) {
    std::vector<int> v{1,2,3,4,5,6};
    EXPECT_TRUE(std::ranges::contains_subrange(v, std::vector<int>{4,5}));
    EXPECT_TRUE(std::ranges::contains_subrange(v, std::vector<int>{4,5}));
    EXPECT_TRUE(pn::contains_subrange(v, std::vector<int>{4,5}));
    EXPECT_FALSE(pn::contains_subrange(v, std::vector<int>{4,9}));
    EXPECT_FALSE(pn::contains_subrange(v, std::vector<int>{1,2,3,4,5,6,7}));
    EXPECT_TRUE(pn::contains_subrange(v, std::vector<int>{1,2,3,4,5,6}));
}


