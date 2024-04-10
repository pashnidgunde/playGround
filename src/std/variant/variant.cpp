#include <cassert>
#include <exception>
#include <stdexcept>
#include <cstring>
#include <utility>

#include <gtest/gtest.h>


// 1. Storage
// 2. Determine type

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
