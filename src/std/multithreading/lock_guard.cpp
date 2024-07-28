#include <vector>
#include <iostream>
#include <mutex>
#include <thread>
// #include <print>
#include <algorithm>

struct Counter {
    int count = 0;
    std::mutex m;
};

struct Account {
    int _b;
    explicit Account(int b) : _b(b) {}
    std::mutex _m;
};

void transfer_lock_guard_adopt_lock(Account &from, Account& to, int amount) {
    auto transfer = [](auto& from, auto& to, int amount) {
        std::lock(from._m, to._m);
        std::lock_guard lg1{from._m, std::adopt_lock};
        std::lock_guard lg2{to._m, std::adopt_lock};
        to._b += amount;
        from._b -= amount;
    };

    for (size_t i = 0; i<1000000; ++i) {
        transfer(from,to,amount);
    }
}

void transfer_unique_lock_defer_lock(Account &from, Account& to, int amount) {
    auto transfer = [](auto& from, auto& to, int amount) {
        std::unique_lock<std::mutex> fl(from._m, std::defer_lock);
        std::unique_lock<std::mutex> tl(to._m, std::defer_lock);
        std::lock(fl, tl);
        to._b += amount;
        from._b -= amount;
    };

    for (size_t i = 0; i<1000000; ++i) {
        transfer(from,to,amount);
    }
}

void transfer_scoped_lock(Account &from, Account& to, int amount) {
    auto transfer = [](auto& from, auto& to, int amount) {
        std::scoped_lock sl(from._m, to._m);
        to._b += amount;
        from._b -= amount;
        
    };

    for (size_t i = 0; i<1000000; ++i) {
        transfer(from,to,amount);
    }
}

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

TEST_F(TestLockGuard, scoped_lock) {
    Account from{10000}, to{100};
    std::jthread t1{transfer_scoped_lock, std::ref(from), std::ref(to), 1};
    std::jthread t2{transfer_scoped_lock, std::ref(to), std::ref(from), 1};

    t1.join();
    t2.join();

    EXPECT_EQ(from._b, 10000);
    EXPECT_EQ(to._b, 100);
}

TEST_F(TestLockGuard, unique_lock_defer_lock) {
    Account from{10000}, to{100};
    std::jthread t1{transfer_unique_lock_defer_lock, std::ref(from), std::ref(to), 1};
    std::jthread t2{transfer_unique_lock_defer_lock, std::ref(to), std::ref(from), 1};

    t1.join();
    t2.join();

    EXPECT_EQ(from._b, 10000);
    EXPECT_EQ(to._b, 100);
}

TEST_F(TestLockGuard, lock_guard_adopt_lock) {
    Account from{10000}, to{100};
    std::jthread t1{transfer_lock_guard_adopt_lock, std::ref(from), std::ref(to), 1};
    std::jthread t2{transfer_lock_guard_adopt_lock, std::ref(to), std::ref(from), 1};

    t1.join();
    t2.join();

    EXPECT_EQ(from._b, 10000);
    EXPECT_EQ(to._b, 100);
}