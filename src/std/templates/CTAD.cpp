// Class Template Argument Deduction
// Meaning : Compiler can deduce the type of the template argument from the constructor
// Programmer doesnt have to specify the type

#include "fmt/format.h"
#include <iostream>
#include <string>
#include <gtest/gtest.h>

template<typename T>
struct SomeClass{
    SomeClass(T val) {
        fmt::println("Val is : {}", val);
    }
};

class TestCTAD : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(TestCTAD, testCTAD) {
    SomeClass x(1);
    static_assert(std::is_same_v<decltype(x),SomeClass<int>>);

    SomeClass y("Hello");
    static_assert(std::is_same_v<decltype(y),SomeClass<const char*>>);

    [[maybe_unused]] std::vector v{1,2,3}; // std::vector<int>
}

