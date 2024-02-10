#include <gtest/gtest.h>
#include <iostream>
// #include <gmock/gmock.h>

namespace samples {
  class A {
  public :
    A() {
      std::cout << "Constructed A";
    }

    ~A() {
      std::cout << "Destructed A";
    }
  };
}


struct RefCount {
private:
    size_t count = 0;
public:
    void increment() {
        count++;
    }

    void decrement() {
        count--;
    }

    [[nodiscard]] bool isZero() const {
        return count == 0;
    }
};

// class MockRefCount : public RefCount {
// public:
//    MOCK_METHOD0(increment, void());
//    MOCK_METHOD0(decrement, void());
//    MOCK_CONST_METHOD0(isZero, bool());
// };


template<typename T>
class shared_pointer {
private:
    RefCount* refCount = nullptr;
    T * ptr = nullptr;
public:
    shared_pointer() {
        ptr = new T();
        refCount = new RefCount();
        refCount->increment();
    }

    ~shared_pointer() {
        refCount->decrement();
        if (refCount->isZero()) {
            delete ptr;
            delete refCount;
        }
    }

    const RefCount* getRefCount() const {
        return refCount;
    }

};



class TestSharedPtr : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(TestSharedPtr, testConstructor) {
    auto ptr = shared_pointer<samples::A>();
    auto refCount =  ptr.getRefCount();
    // EXPECT_EQ(refCount)

}

TEST_F(TestSharedPtr, testDestructor) {
    MockRefCount refCount;
    auto ptr = shared_pointer<samples::A>();
    }
    // EXPECT_CALL(refCount, decrement()).Times(testing::Exactly(1));
}

