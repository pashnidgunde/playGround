#include <iostream>

template<typename T>
concept SupportsLessThan = requires (T t) { t < t; };

template<typename T>
requires std::copyable<T> and SupportsLessThan<T>
T mmax(T lhs, T rhs) {
  return lhs < rhs ? rhs : lhs;
}

#include <gtest/gtest.h>

class TestConcepts : public ::testing::Test {
  protected:
      void SetUp() override {}
      void TearDown() override {}
  };
  
TEST_F(TestConcepts, testConcept) {
    int a = 1;
    int b = 2;
    EXPECT_EQ(mmax(a,b) , 2);

    std::unique_ptr<int> ptr1, ptr2;
    // EXPECT_EQ(mmax(ptr1,ptr2) , ptr1);
}