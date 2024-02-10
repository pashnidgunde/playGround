#include <gtest/gtest.h>
#include <iostream>
#include <utility>
#include <memory>
// #include <gmock/gmock.h>

namespace samples {
  class A {
  public :
    A() {
      std::cout << "Constructed A";
    }

    A(int x) {
        this->x = x;
    }

    ~A() {
      std::cout << "Destructed A";
    }

  private :
      int x;
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

    size_t getCount() const {
        return count;
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
    using Type = T;
    RefCount* refCount = nullptr;
    T * ptr = nullptr;
public:

    shared_pointer(shared_pointer<T>& other) {
        this->refCount = other.refCount;
        this->refCount->increment();
    }

    shared_pointer& operator=(shared_pointer<T>& other) {
        if (this == &other) {
            return *this;
        }

        free();

        this->refCount = other.refCount;
        this->refCount->increment();
    }

    template<typename Arg>
    shared_pointer(Arg arg) {
        ptr = new Type(std::forward<Arg>(arg));
        refCount = new RefCount();
        refCount->increment();
    }

    template<typename ...Args>
    shared_pointer(Args&&... args) {
        ptr = new Type(std::forward<Args>(args)...);
        refCount = new RefCount();
        refCount->increment();
    }

    ~shared_pointer() {
        free();
    }

    void free() {
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

namespace pn {
    template<typename T, typename ...Args>
    shared_pointer<T> make_shared(Args&& ...args) {
        return shared_pointer<T>(std::forward<Args>(args)...);
    }
}


class TestSharedPtr : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(TestSharedPtr, testConstructor) {
    auto ptr = shared_pointer<samples::A>();
    auto refCount =  ptr.getRefCount();
    EXPECT_EQ(refCount->getCount(),1);
}

TEST_F(TestSharedPtr, testConstructorWithArgs) {
    auto ptr = shared_pointer<samples::A>(1);
    auto refCount =  ptr.getRefCount();
    EXPECT_EQ(refCount->getCount(),1);
}

TEST_F(TestSharedPtr, testMakeShared) {
    auto ptr = pn::make_shared<samples::A>();
    auto refCount =  ptr.getRefCount();
    EXPECT_EQ(refCount->getCount(),1);
}

TEST_F(TestSharedPtr, testCopy) {
    auto ptr = pn::make_shared<samples::A>();
    auto refCount =  ptr.getRefCount();
    EXPECT_EQ(refCount->getCount(),1);

    [[maybe_unused]] auto ptr1(ptr);
    EXPECT_EQ(ptr1.getRefCount(),ptr.getRefCount());
}

TEST_F(TestSharedPtr, testScope) {
    auto ptr = pn::make_shared<samples::A>();
    auto refCount =  ptr.getRefCount();
    EXPECT_EQ(refCount->getCount(),1);

    {
        [[maybe_unused]] auto ptr1(ptr);
        EXPECT_EQ(ptr1.getRefCount(), ptr.getRefCount());
    }
    EXPECT_EQ(refCount->getCount(),1);
}

TEST_F(TestSharedPtr, testEqual) {
    auto ptr = pn::make_shared<samples::A>();
    auto refCount =  ptr.getRefCount();
    EXPECT_EQ(refCount->getCount(),1);
    shared_pointer<samples::A> ptr1 = ptr;
    EXPECT_EQ(ptr1.getRefCount(), ptr.getRefCount());
    EXPECT_EQ(refCount->getCount(),2);
}

TEST_F(TestSharedPtr, testEqualScoped) {
    auto ptr = pn::make_shared<samples::A>();
    auto refCount =  ptr.getRefCount();
    EXPECT_EQ(refCount->getCount(),1);

    {
        [[maybe_unused]] auto ptr1 = ptr;
        EXPECT_EQ(ptr1.getRefCount(), ptr.getRefCount());
    }
    EXPECT_EQ(refCount->getCount(),1);
}