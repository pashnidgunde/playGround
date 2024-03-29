#include <cassert>
#include <exception>
#include <stdexcept>
#include <cstring>
#include <utility>

#include <gtest/gtest.h>


namespace pn {
  template<typename ...Ts>
  struct Variant {
  };
}

class TestVariant : public ::testing::Test {
protected:
  void SetUp() override {}
  void TearDown() override {}
};

TEST_F(TestVariant, testConstructor) {
}
