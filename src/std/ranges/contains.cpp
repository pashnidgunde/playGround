#include <algorithm>
#include <vector>

namespace pn {
    template<typename Iter, typename T>
    bool contains(Iter begin, const Iter& end, const T& val) {
        while(begin != end) {
            if (*begin == val) {
                return true;
            }
            ++begin;
        }
        return false;
    }

    template<typename C>
    bool contains(const C& hayStack, const typename C::value_type& needle) {
        return contains(hayStack.begin(), hayStack.end(), needle);
    }

    template<typename Iter>
    bool contains_subrange(const Iter& hBegin, const Iter& hEnd,
        const Iter& nBegin, const Iter& nEnd) {
        auto needleIter{nBegin};
        auto hayStackBegin{hBegin};
        while(hayStackBegin != hEnd && needleIter != nEnd) {
            if (*needleIter != *hayStackBegin) {
                needleIter = nBegin;
            } else {
                ++needleIter;
            }
            ++hayStackBegin;
        }
        return needleIter == nEnd;
    }


    template<typename C>
    bool contains_subrange(const C& hayStack, const C& needle) {
        return contains_subrange(hayStack.begin(),
            hayStack.end(),
            needle.begin(),
            needle.end());
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

TEST_F(TestContains, testOneIL) {
    auto hay_stack = std::initializer_list<int>{1,2,3,4,5};
    EXPECT_TRUE(std::ranges::contains(hay_stack, 4));
    EXPECT_TRUE(pn::contains(hay_stack,4));
    EXPECT_FALSE(pn::contains(hay_stack,10));

    std::vector<int> v{1,2,3,4,5};
    EXPECT_TRUE(std::ranges::contains(v, 4));
    EXPECT_TRUE(pn::contains(v,4));
    EXPECT_FALSE(pn::contains(v,10));
}

TEST_F(TestContains, testILRange) {
    auto hay_stack = std::initializer_list<int>{1,2,3,4,5};
    EXPECT_TRUE(std::ranges::contains_subrange(hay_stack, std::initializer_list<int>{4,5}));
    EXPECT_TRUE(pn::contains_subrange(hay_stack, std::initializer_list<int>{4,5}));
    
    EXPECT_FALSE(pn::contains_subrange(hay_stack, std::initializer_list<int>{4,9}));
    EXPECT_FALSE(pn::contains_subrange(hay_stack, std::initializer_list<int>{1,2,3,4,5,6,7}));
    EXPECT_FALSE(pn::contains_subrange(hay_stack, std::initializer_list<int>{1,2,3,4,5,6}));
}

TEST_F(TestContains, testVectorRange) {
    std::vector<int> v{1,2,3,4,5,6};
    EXPECT_TRUE(std::ranges::contains_subrange(v, std::vector<int>{4,5}));
    EXPECT_TRUE(pn::contains_subrange(v, std::vector<int>{4,5}));

    EXPECT_FALSE(pn::contains_subrange(v, std::vector<int>{4,9}));
    EXPECT_FALSE(pn::contains_subrange(v, std::vector<int>{1,2,3,4,5,6,7}));
    EXPECT_TRUE(pn::contains_subrange(v, std::vector<int>{1,2,3,4,5,6}));
}
