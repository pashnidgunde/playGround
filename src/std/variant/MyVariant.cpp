#include <string>
#include <stdexcept>
#include <gtest/gtest.h>

struct MyVariant {

  enum class Type {
    EMPTY,
    INT,
    STRING,
  };
  Type value_type{Type::EMPTY};

  union {
    int _int;
    std::string _string;
  };


  explicit MyVariant(int x) : value_type(Type::INT), _int(x) {
  }

  explicit MyVariant(const std::string& v) : value_type{Type::STRING}, _string(v) {
  }

  explicit MyVariant(std::string&& v) : value_type{Type::STRING}, _string(std::move(v)) {
  }

  ~MyVariant() {
    // Needs explicit destructor
    // UB if not checked and called destructor on empty string
    if (value_type == Type::STRING) {
      _string.~basic_string();
    }
  }

  void get(int& value) const {
    if (value_type != Type::INT) {
      throw std::runtime_error("No such value");
    }
    value = _int;
  }

  void get(std::string& value) const {
    if (value_type != Type::STRING) {
      throw std::runtime_error("No such value");
    }
    value = _string;
  }



};

class TestMyVariant : public ::testing::Test {
protected:
  void SetUp() override {}
  void TearDown() override {}
};

TEST_F(TestMyVariant, testInt) {
  MyVariant v(10);
  int x = 0;
  v.get(x);
  EXPECT_EQ(x,10);
}

TEST_F(TestMyVariant, testString) {
  MyVariant v(10);
  int x = 0;
  v.get(x);
  EXPECT_EQ(x,10);
}
