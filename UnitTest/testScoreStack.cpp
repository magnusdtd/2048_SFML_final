#include "pch.h"
#include "../2048_SFML/ScoreStack.hpp"
#include "../2048_SFML/ScoreStack.cpp"

// Test the default constructor
TEST(ScoreStackTest, DefaultConstructor) {
    ScoreStack stack;
    EXPECT_TRUE(stack.empty());
}

// Test the copy constructor
TEST(ScoreStackTest, CopyConstructor) {
    ScoreStack original;
    original.push(10);
    original.push(20);

    ScoreStack copy(original);
    EXPECT_EQ(copy.top(), 20);
    copy.pop();
    EXPECT_EQ(copy.top(), 10);
}

// Test push and top
TEST(ScoreStackTest, PushAndTop) {
    ScoreStack stack;
    stack.push(42);
    EXPECT_EQ(stack.top(), 42);
    stack.push(100);
    EXPECT_EQ(stack.top(), 100); // The last pushed value should be on top
}

// Test pop
TEST(ScoreStackTest, Pop) {
    ScoreStack stack;
    stack.push(1);
    stack.push(2);
    stack.pop();
    EXPECT_EQ(stack.top(), 1); // After popping, the top should now be the first element
    stack.pop();
    EXPECT_TRUE(stack.empty()); // After popping everything, the stack should be empty
}

// Test empty
TEST(ScoreStackTest, Empty) {
    ScoreStack stack;
    EXPECT_TRUE(stack.empty()); // Initially, the stack should be empty
    stack.push(10);
    EXPECT_FALSE(stack.empty()); // After pushing, it should not be empty
    stack.pop();
    EXPECT_TRUE(stack.empty()); // After popping the only element, it should be empty again
}

// Main function for the test runner
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
