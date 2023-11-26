#include <gtest/gtest.h>
#include "HammingDistance.h"

class TestHammingDistance : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(TestHammingDistance, testCases) {
#ifdef __GNUC__
    EXPECT_EQ(Solution::hammingDistance(1,4), 2);
    EXPECT_EQ(Solution::hammingDistance(3,1), 1);
#endif

    EXPECT_EQ(Solution::hammingDistanceIter(1,4), 2);
    EXPECT_EQ(Solution::hammingDistanceIter(3,1), 1);

    EXPECT_EQ(Solution::hammingDistanceBitSet(1,4), 2);
    EXPECT_EQ(Solution::hammingDistanceBitSet(3,1), 1);
}



