#include "pch.h"
#include "../2048_SFML/utils.hpp"
#include "../2048_SFML/utils.cpp"

#include <limits>

// Test the Random function with integer type
TEST(UtilsTest, RandomInteger) {
    int start = 0;
    int end = 10;
    int randomValue = Random(start, end);
    EXPECT_GE(randomValue, start);
    EXPECT_LE(randomValue, end);
}

// Test the Random function with floating point type
TEST(UtilsTest, RandomFloat) {
    float start = 0.0f;
    float end = 1.0f;
    float randomValue = Random(start, end);
    EXPECT_GE(randomValue, start);
    EXPECT_LE(randomValue, end);
}

// Test the generateRandomString function
TEST(UtilsTest, GenerateRandomString) {
    u32 length = 10;
    std::string randomString = generateRandomString(length);
    EXPECT_EQ(randomString.length(), length);
}

// Test the generateRandomString function with zero length
TEST(UtilsTest, GenerateRandomStringZeroLength) {
    u32 length = 0;
    std::string randomString = generateRandomString(length);
    EXPECT_TRUE(randomString.empty());
}
