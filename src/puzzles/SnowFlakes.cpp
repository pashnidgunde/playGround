/* Problem Name is &&& Snowpack &&& PLEASE DO NOT REMOVE THIS LINE. */

/*
** Instructions to candidate.
**  1) Given an array of non-negative integers representing the elevations
**     from the vertical cross section of a range of hills, determine how
**     many units of snow could be captured between the hills.
**
**     See the example array and elevation map below.
**                                 ___
**             ___                |   |        ___
**            |   |        ___    |   |___    |   |
**         ___|   |    ___|   |   |   |   |   |   |
**     ___|___|___|___|___|___|___|___|___|___|___|___
**     {0,  1,  3,  0,  1,  2,  0,  4,  2,  0,  3,  0} = heights
**                                 ___
**             ___                |   |        ___
**            |   | *   *  _*_  * |   |_*_  * |   |
**         ___|   | *  _*_|   | * |   |   | * |   |
**     ___|___|___|_*_|___|___|_*_|___|___|_*_|___|___
**     {0,  1,  3,  0,  1,  2,  0,  4,  2,  0,  3,  0}
**
**
**
**
**
**     Solution: In this example 13 units of snow (*) could be captured.
**
**  2) Consider adding some additional tests in doTestsPass().
**  3) Implement computeSnowpack() correctly.
*/

// 0,1,3,3,3,3,3,4,4,4,4,4
// 4,4,4,4,4,4,4,4,3,3,3,0

// 0,1,0,3,2,3,0,0,1,3,0,0



#include <gtest/gtest.h>
#include <vector>
#include <ranges>

class SnowFlakes {
    public :
        static int computeSnowpack(const std::vector<int>& inputs) {
            std::vector<int> maxFromLeft;
            maxFromLeft.reserve(inputs.size());
            auto maxSoFar{INT_MIN};
            for(const auto& input : inputs) {
                maxSoFar = std::max(maxSoFar, input);
                maxFromLeft.emplace_back(maxSoFar);
            }

            std::vector<int> maxFromRight(inputs.size());
            size_t index{inputs.size() - 1};

            maxSoFar = INT_MIN;
            for (auto input : inputs | std::views::reverse) {
                 maxSoFar = std::max(maxSoFar,input);
                 maxFromRight[index] = maxSoFar;
                 index--;
            }

            int result{0};
            for (size_t i=0; i<inputs.size(); i++) {
                 result += (std::min(maxFromLeft[i], maxFromRight[i]) - inputs[i]);
            }
            return result;
        }
};


class TestSnowFlakes : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(TestSnowFlakes, testCases) {
    std::vector<int> input{0, 1, 3, 0, 1, 2, 0, 4, 2, 0, 3, 0};
    
    EXPECT_EQ(SnowFlakes::computeSnowpack(input), 13);

}