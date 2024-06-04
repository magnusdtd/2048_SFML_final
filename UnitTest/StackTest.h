#include "gtest/gtest.h"
#include "utils.hpp"

class StackTest : public ::testing::Test {
protected:
    Stack stack;
};

TEST_F(StackTest, EmptyOnCreation) {
    EXPECT_TRUE(stack.empty());
}

TEST_F(StackTest, NotEmptyAfterPush) {
    u64 data[] = {1, 2, 3, 4, 5};
    stack.push(data, 5);
    EXPECT_FALSE(stack.empty());
}

TEST_F(StackTest, EmptyAfterPop) {
    u64 data[] = {1, 2, 3, 4, 5};
    stack.push(data, 5);
    stack.pop();
    EXPECT_TRUE(stack.empty());
}

TEST_F(StackTest, TopReturnsLastPushedValue) {
    u64 data1[] = {1, 2, 3, 4, 5};
    u64 data2[] = {6, 7, 8, 9, 10};
    stack.push(data1, 5);
    stack.push(data2, 5);
    u64* topData = stack.top();
    for (u32 i = 0; i < 5; i++) {
        EXPECT_EQ(topData[i], data2[i]);
    }
}

TEST_F(StackTest, PopRemovesTopValue) {
    u64 data1[] = {1, 2, 3, 4, 5};
    u64 data2[] = {6, 7, 8, 9, 10};
    stack.push(data1, 5);
    stack.push(data2, 5);
    stack.pop();
    u64* topData = stack.top();
    for (u32 i = 0; i < 5; i++) {
        EXPECT_EQ(topData[i], data1[i]);
    }
}
