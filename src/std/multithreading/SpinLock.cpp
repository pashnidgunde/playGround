#include <thread>
#include <atomic>
#include <iostream>

// spin lock using atomic bool

class SpinLockDemo {
    int shared_data = 0;
    std::atomic<bool> lock = false;

public:

    void increment() {
        while(lock.exchange(true)) {
            // spin
        }
        shared_data++;
        lock = false;
    }

    void decrement() {
        while(lock.exchange(true)) {
            // spin
        }
        shared_data--;
        lock = false;
    }

    void demo() {
        std::thread t1([&](){
            for (size_t i =0; i< 10000000; ++i) {
                increment();
            }
        });

        std::thread t2([&](){
            for (size_t i =0; i< 10000000; ++i) {
                decrement();
            }
        });

        t1.join();
        t2.join();
    }

    int getShared() const { return shared_data; }
};

#include <gtest/gtest.h>

class TestSpinLockDemo : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(TestSpinLockDemo, test1) {
    SpinLockDemo spinLockDemo;
    spinLockDemo.demo();
    EXPECT_EQ(spinLockDemo.getShared(), 0);
}