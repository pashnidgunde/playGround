#include <thread>
#include <chrono>
#include <future>
#include <iostream>
#include <fmt/format.h>

class FuturePromiseDemo {
    private:
        std::promise<int> p;
        int x = 0;
    public:
        void demo() {
            std::thread t1([&](){
                std::this_thread::sleep_for(std::chrono::seconds(1));
                p.set_value(100);
            });            

            // p.get_future can be called only once
            std::thread t2([&](auto f){
                // waits until t1 finishes
                std::cout << "Data is : " << f.get() << std::endl;
                x = f.get();
            }, p.get_future());

            t1.join();
            t2.join();
        }
        int getData() const { return x; }

        void demoTwo() 
        {
            fmt::println("In demo2");

            std::promise<int> p;
            std::future f = p.get_future();

            std::promise<long> mp;
            std::future mf = mp.get_future();

            std::thread t1([&p]() {
                auto x = 1;
                for(size_t i=0; i<10000; ++i) {
                    x = x * rand() % 10;
                }
                p.set_value(x);
            });

            std::thread t2([&f, &mp]() {
                // Blocking call until t1 finishes
                fmt::println("future value from t1 is : {}", f.get());
                mp.set_value(f.get() * 1000000);
            });

            // Main is blocking for t2 to finish
            fmt::println("Main future value is : {}", mf.get());

            t1.join();
            t2.join();
            
        }

};

#include <gtest/gtest.h>
class TestFuturePromise : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(TestFuturePromise, testOne) {
    FuturePromiseDemo futurePromiseDemo;
    {
        futurePromiseDemo.demo();
        EXPECT_EQ(futurePromiseDemo.getData(), 100);
    }
    {
        futurePromiseDemo.demoTwo();
    }
}
