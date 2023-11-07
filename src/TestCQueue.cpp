#include <gtest/gtest.h>
#include "CQueue.h"

class TestSPSCQueue : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(TestSPSCQueue, testCases) {
    CQueue<int,3> myCircularQueue;
    EXPECT_TRUE(myCircularQueue.isEmpty());
    EXPECT_FALSE(myCircularQueue.isFull());
    EXPECT_TRUE(myCircularQueue.enQueue(1)); // return True
    EXPECT_TRUE(myCircularQueue.enQueue(2)); // return True
    EXPECT_TRUE(myCircularQueue.enQueue(3)); // return True
    EXPECT_EQ(myCircularQueue.Front(),1);     // return 3
    EXPECT_FALSE(myCircularQueue.enQueue(4)); // return False
    EXPECT_EQ(myCircularQueue.Rear(),3);     // return 3
    EXPECT_TRUE(myCircularQueue.isFull());   // return True
    EXPECT_TRUE(myCircularQueue.deQueue());  // return True
    EXPECT_TRUE(myCircularQueue.enQueue(4)); // return True
    EXPECT_EQ(myCircularQueue.Rear(),4);     // return 4
}
