#include <thread>
#include <fmt/format.h>
#include <fmt/std.h>

struct ThreadDemo {

  void demo() {
    std::thread t1([](){
      fmt::println("ThreadId : {}", std::this_thread::get_id());
    });

    // passing 100 to thread t2
    std::thread t2([](int x){
      fmt::println("ThreadId : {}", std::this_thread::get_id());
      fmt::println("Passed value : {}", x);
    }, 100);

    t1.join();
    t2.join();
  }
};



#include <gtest/gtest.h>

class TestThreadDemo : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(TestThreadDemo, test1) {
    ThreadDemo td;
    td.demo();
    
}