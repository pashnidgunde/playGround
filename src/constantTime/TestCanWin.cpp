//https://leetcode.com/problems/nim-game/description/
#include <gtest/gtest.h>
class CanWin {
public:
    static bool canWinNim(int n) {
        return (n % 4 != 0);
    }
};

class TestCanWin : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(TestCanWin, testCases) {
    EXPECT_TRUE(CanWin::canWinNim(1));
    EXPECT_TRUE(CanWin::canWinNim(2));
    EXPECT_TRUE(CanWin::canWinNim(3));
    EXPECT_FALSE(CanWin::canWinNim(4));
    EXPECT_FALSE(CanWin::canWinNim(8));
    EXPECT_FALSE(CanWin::canWinNim(16));
}
