//https://leetcode.com/problems/design-circular-queue/description/
/*
 * Design your implementation of the circular queue. The circular queue is a linear data structure in which the operations are performed based on FIFO (First In First Out) principle, and the last position is connected back to the first position to make a circle. It is also called "Ring Buffer".

One of the benefits of the circular queue is that we can make use of the spaces in front of the queue. In a normal queue, once the queue becomes full, we cannot insert the next element even if there is a space in front of the queue. But using the circular queue, we can use the space to store new values.

Implement the CQueue class:

CQueue(k) Initializes the object with the size of the queue to be k.
int Front() Gets the front item from the queue. If the queue is empty, return -1.
int Rear() Gets the last item from the queue. If the queue is empty, return -1.
boolean enQueue(int value) Inserts an element into the circular queue. Return true if the operation is successful.
boolean deQueue() Deletes an element from the circular queue. Return true if the operation is successful.
boolean isEmpty() Checks whether the circular queue is empty or not.
boolean isFull() Checks whether the circular queue is full or not.
You must solve the problem without using the built-in queue data structure in your programming language.



Example 1:

Input
["CQueue", "enQueue", "enQueue", "enQueue", "enQueue", "Rear", "isFull", "deQueue", "enQueue", "Rear"]
[[3], [1], [2], [3], [4], [], [], [], [4], []]
Output
[null, true, true, true, false, 3, true, true, true, 4]

Explanation
CQueue CQueue = new CQueue(3);
CQueue.enQueue(1); // return True
CQueue.enQueue(2); // return True
CQueue.enQueue(3); // return True
CQueue.enQueue(4); // return False
CQueue.Rear();     // return 3
CQueue.isFull();   // return True
CQueue.deQueue();  // return True
CQueue.enQueue(4); // return True
CQueue.Rear();     // return 4

 */

#include <array>
#include <gtest/gtest.h>

template<typename T, size_t CAPACITY>
class CQueue {
public:
    bool enQueue(int value) {
        if (isFull()) {
            return false;
        }
        if (rear == -1) {
            front = rear = 0;
        }
        else {
            rear = (rear + 1) % CAPACITY;
        }

        container[rear] = value;
        size++;

        return true;
    }

    bool deQueue() {
        if (isEmpty())  {
            return false;
        }
        front = (front + 1) % CAPACITY;
        size--;

        return true;
    }

    T Front() {
        return isEmpty() ? -1 : container[front];
    }

    T Rear() {
        return isEmpty() ? -1 : container[rear];
    }

    bool isEmpty() {
        return size == 0;
    }

    bool isFull() {
        return size == CAPACITY;
    }

    size_t size = 0;
    int front = -1;
    int rear = -1;
    std::array<T, CAPACITY> container;
};


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
