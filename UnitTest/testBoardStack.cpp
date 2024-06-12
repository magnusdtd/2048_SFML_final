#include "pch.h"
#include "../2048_SFML/BoardStack.hpp"
#include "../2048_SFML/BoardStack.cpp"

TEST(BoardStackTest, PushPopTop) {
    BoardStack stack;
    u64 *data1 = new u64[4]{ 1, 2, 3, 4 };
    u64 *data2 = new u64[4]{ 5, 6, 7, 8 };
    u64 *data3 = new u64[4]{ 9, 10, 11, 12 };

    stack.push(data1, 4);
    stack.push(data2, 4);
    stack.push(data3, 4);

    u64 *temp = stack.top();
    for (int i = 0; i < 4; i++)
		EXPECT_EQ(temp[i], data3[i]);
    stack.pop();
    temp = stack.top();
    for (int i = 0; i < 4; i++)
        EXPECT_EQ(temp[i], data2[i]);
    stack.pop();
    temp = stack.top();
    for (int i = 0; i < 4; i++)
        EXPECT_EQ(temp[i], data1[i]);
    stack.pop();
    EXPECT_TRUE(stack.empty());

    delete[] data1;
    delete[] data2;
    delete[] data3;
}