#include "pch.h"
#include "../2048_SFML/ScoreStack.hpp"
#include "../2048_SFML/ScoreStack.cpp"

TEST(ScoreStackTest, PushPopTop) {
    ScoreStack stack;
    stack.push(10);
    stack.push(20);
    stack.push(30);

    EXPECT_EQ(stack.top(), 30);
    stack.pop();
    EXPECT_EQ(stack.top(), 20);
    stack.pop();
    EXPECT_EQ(stack.top(), 10);
    stack.pop();
    EXPECT_TRUE(stack.empty());
}