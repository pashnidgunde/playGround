/*
https://leetcode.com/problems/hamming-distance/
The Hamming distance between two integers is the number of positions at which the corresponding bits are different.
Given two integers x and y, return the Hamming distance between them.

Input: x = 1, y = 4
Output: 2
Explanation:
1   (0 0 0 1)
4   (0 1 0 0)
↑   ↑
The above arrows point to positions where the corresponding bits are different.
*/

#include <bitset>
#ifdef __GNUC__
#include <bits/stdc++.h>
#endif

#include <gtest/gtest.h>

class HammingDistance {
public:
    template<typename T>
    static int hammingDistanceIter(T x, T y) {
        static constexpr size_t BITS_PER_BYTES = 8;
        static constexpr size_t limit = (sizeof(T) * BITS_PER_BYTES);
        int count = 0;
        for (size_t i = 0; i< limit; ++i) {
            auto xLastBit = x & 1;
            auto yLastBit = y & 1;
            if (xLastBit != yLastBit) count++;
            x = x >> 1;
            y = y >> 1;
        }
        return count;
    }

    template<typename T>
    static int hammingDistanceBitSet(T x, T y) {
        int count = 0;
        auto xAsStr = std::bitset<sizeof(T)>(x).to_string();
        auto yAsStr = std::bitset<sizeof(T)>(y).to_string();
        for (size_t i=0; i<xAsStr.size(); ++i) {
            if (xAsStr[i] != yAsStr[i]) {
                count++;
            }
        }
        return count;
    }

#ifdef __GNUC__
    template<typename T>
    static int hammingDistance(T x, T y) {
        return __builtin_popcountll(x^y);
    }
#endif

};

class TestHammingDistance : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(TestHammingDistance, testCases) {
#ifdef __GNUC__
    EXPECT_EQ(HammingDistance::hammingDistance(1,4), 2);
    EXPECT_EQ(HammingDistance::hammingDistance(3,1), 1);
#endif

    EXPECT_EQ(HammingDistance::hammingDistanceIter(1,4), 2);
    EXPECT_EQ(HammingDistance::hammingDistanceIter(3,1), 1);

    EXPECT_EQ(HammingDistance::hammingDistanceBitSet(1,4), 2);
    EXPECT_EQ(HammingDistance::hammingDistanceBitSet(3,1), 1);
}
