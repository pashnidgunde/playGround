#include <thread>
#include <atomic>
#include <mutex>

struct SpinLock {
  std::atomic_flag flag = ATOMIC_FLAG_INIT;

  void lock() {
    // while(flag.test_and_set());
    while(flag.test_and_set(std::memory_order_acquire));
  }

  void unlock() {
    // flag.clear();
    flag.clear(std::memory_order_release);
  }

};


SpinLock spin;
//std::mutex spin;
int shared_data = 0;

// lock and unlock calls through lock_guard
void decrement() {
  std::lock_guard<SpinLock> lg(spin);
  shared_data ++;
}

// lock and unlock direct calls
void increment() {
  spin.lock();
  shared_data --;
  spin.unlock();
}

#include <gtest/gtest.h>

class TestSpinLockAF : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(TestSpinLockAF, testAtomicFlag) {
    std::thread t1([](){
      for (size_t i=0; i<100000; ++i) {
        increment();
      }
    });
  
    std::thread t2([](){
      for (size_t i=0; i<100000; ++i) {
        decrement();
      }
    });

    t1.join();
    t2.join();
    EXPECT_EQ(shared_data, 0);
}