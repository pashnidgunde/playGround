#include <thread>
#include <atomic>

struct SpinLock {
  std::atomic_flag flag {ATOMIC_FLAG_INIT};

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

void work() {
  spin.lock();
  // cs
  spin.unlock();
}

int main() {
  std::thread t1(work);
  std::thread t2(work);

  t1.join();
  t2.join();

  return 0;
}