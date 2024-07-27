#include <vector>
#include <iostream>
#include <mutex>
#include <thread>

struct Counter {
    int count = 0;
    std::mutex m;
};

#include <gtest/gtest.h>
class TestLockGuard : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(TestLockGuard, test1) {
    std::vector<std::thread> runners;
    Counter c;
    for (size_t i=0; i<5; ++i) {
        runners.emplace_back([&c]() {
            std::lock_guard<std::mutex> lg(c.m);
            ++c.count;
        });
    }

    for (auto& runner : runners) {
        runner.join();
    }
    EXPECT_EQ(c.count, 5);
}

TEST_F(TestLockGuard, testWithJthread) {
    std::vector<std::jthread> runners;
    Counter c;
    for (size_t i=0; i<5; ++i) {
        runners.emplace_back([&c]() {
            std::lock_guard<std::mutex> lg(c.m);
            ++c.count;
        });
    }

    // calls joins
    runners.clear();

    EXPECT_EQ(c.count, 5);
}