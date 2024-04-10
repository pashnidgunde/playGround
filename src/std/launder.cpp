#include<cassert>
#include <iostream>
#include <gtest/gtest.h>

// New format : // new T (value);
// auto *x = new X(10)


// placement new format : // new (address) T (value)
// X x(20);
// new (&x)(30);


class TestLaunder : public ::testing::Test {
protected:
  void SetUp() override {}
  void TearDown() override {}
};

TEST_F(TestLaunder, placmentNew) {
    // alloc
    int *ptr = new int(10);

    // placement new
    new (ptr) int(20);

    // placement new, new ptr
    int *xyz = new (ptr) int(30);

    EXPECT_EQ(xyz, ptr);
    EXPECT_EQ(*xyz, *ptr);
    delete ptr;
}

TEST_F(TestLaunder, placmentNewArr) {
  // placement new in contiguos memory
    int arr[2] = {0, 0};

    new(arr) int (20);
    EXPECT_EQ(arr[0],20);

    new(arr+1) int(10);
    EXPECT_EQ(arr[1],10);
}

TEST_F(TestLaunder, placmentNewStruct) {
    struct X {
      int n;
      double m;
    };

    X *ptr = new X{10,20};

    new (ptr) X{100,200};

    EXPECT_EQ(ptr->n, 100);
    EXPECT_EQ(ptr->m, 200);

    delete ptr;
}

TEST_F(TestLaunder, placmentNewStructUndefBehav) {
    // making a member const or volatile is undefined behavior
    struct X {
      const int n;        // const makes
      double m;
    };

    X* x = new X{10,20};

    new (x) X{100,200};
    // std::cout << x->n << std::endl;  // undefined behavior
    // std::cout << x->m << std::endl;  // undefined behavior
    EXPECT_EQ(x->n, 100);
    EXPECT_EQ(x->m, 200);

    delete x;
}

TEST_F(TestLaunder, placmentNewStructNoUB) {
    // make a new pointer from original
    struct X {
      const int n;        // const makes
      double m;
    };

    X* x = new X{10,20};
    [[maybe_unused]] X* other = new (x) X{100,200};

    // std::cout << other->n << std::endl;  // NO UB on a new pointer
    // std::cout << other->m << std::endl;  // NO UB on a new pointer

    assert(other->n == 100);
    assert(other->m == 200);

    delete x;
}

TEST_F(TestLaunder, safeLaunder) {
    struct X {
      const int n;        // const
      double m;
    };

    X x = X{10,20};

    new (&x) X{100,200};

    // std::cout << std::launder(&x)->n << std::endl;  // no undefined behavior
    // std::cout << std::launder(&x)->n << std::endl;  // not underfined behavior

    assert(x.n == 100);
    assert(x.m == 200);
}
