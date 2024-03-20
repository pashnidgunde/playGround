#include <variant>
#include <type_traits>
#include <gtest/gtest.h>

template<template <typename ...> class NamedTemplate>
using MyType = NamedTemplate<int,double,float>;

using TupleType = MyType<std::tuple>;
using VariantType = MyType<std::variant>;

class TestTTA : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(TestTTA, testTTA) {
    static_assert(std::is_same_v<TupleType, std::tuple<int,double,float>>);
    static_assert(std::is_same_v<VariantType , std::variant<int,double,float>>);
}