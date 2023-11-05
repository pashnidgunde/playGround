#include <gtest/gtest.h>
#include "CanWin.h"

class TestCanWin : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(TestCanWin, testCases) {
    EXPECT_TRUE(Solution::canWinNim(1));
    EXPECT_TRUE(Solution::canWinNim(2));
    EXPECT_TRUE(Solution::canWinNim(3));
    EXPECT_FALSE(Solution::canWinNim(4));
    EXPECT_FALSE(Solution::canWinNim(8));
    EXPECT_FALSE(Solution::canWinNim(16));
}
