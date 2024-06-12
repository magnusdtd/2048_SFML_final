#include "pch.h"
#include "../2048_SFML/BigInteger.hpp"
#include "../2048_SFML/BigInteger.cpp"

TEST(BigIntegerTest, Addition) {
    BigInteger a("123");
    BigInteger b("456");
    BigInteger result = a + b;
    EXPECT_EQ(result.getValue(), "579");
}

TEST(BigIntegerTest, Subtraction) {
    BigInteger a("456");
    BigInteger b("123");
    BigInteger result = a - b;
    EXPECT_EQ(result.getValue(), "333");
}

TEST(BigIntegerTest, Multiplication) {
    BigInteger a1("123");
    BigInteger b1("456");
    BigInteger result1 = a1 * b1;
    EXPECT_EQ(result1.getValue(), "56088");

    BigInteger a2("123456789");
    BigInteger b2("987654321");
    BigInteger result2 = a2 * b2;
    EXPECT_EQ(result2.getValue(), "121932631112635269");
}

TEST(BigIntegerTest, Equality) {
    BigInteger a("123");
    BigInteger b("123");
    EXPECT_TRUE(a == b);
}

TEST(BigIntegerTest, GreaterOrEqual) {
    BigInteger a("456");
    BigInteger b("123");
    EXPECT_TRUE(a >= b);
}

TEST(BigIntegerTest, Divide) {
    BigInteger a("123");
    BigInteger b("2");
    BigInteger result = a / b;
    EXPECT_EQ(result.getValue(), "61");
}

TEST(BigIntegerTest, Modulus) {
    BigInteger a("123");
    BigInteger b("2");
    BigInteger result = a % b;
    EXPECT_EQ(result.getValue(), "1");
}

TEST(BigIntegerTest, Negative) {
    BigInteger a("-123");
    BigInteger b("456");
    BigInteger result = a + b;
    EXPECT_EQ(result.getValue(), "333");
    result = a - b;
    EXPECT_EQ(result.getValue(), "-579");
    result = a * b;
    EXPECT_EQ(result.getValue(), "-56088");
    result = a / b;
    EXPECT_EQ(result.getValue(), "0");
    result = a % b;
    EXPECT_EQ(result.getValue(), "-123");
}
